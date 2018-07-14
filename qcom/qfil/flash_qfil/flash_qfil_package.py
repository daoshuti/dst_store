#!/usr/bin/env python

# Copyright 2017-present Facebook. All Rights Reserved.
#
# This script update firmware and OS images using Qualcomm's Firehose protocol and
# Firehose Validated Image Programming (VIP). Reference: Qualcomm's 80-P9116-1.
#

import argparse
import glob
import os
import platform
import subprocess
import sys
from xml.etree import ElementTree as ET


def get_vendor_and_product_ids(uevent_path):
    # Get the product and product IDs from uevent node
    ids = list()
    with open(uevent_path, 'r') as uevent_file:
        lines = uevent_file.readlines()
        for line in lines:
            line = line.strip()
            if line.startswith('PRODUCT'):
                ids = line.split('=')[1].split('/')
                break
    uevent_file.close()
    return ids


def is_windows():
    # Return True if running on Windows operating system
    return platform.system() == 'Windows'


def get_edl_device():
    # Autodetect first EDL device or use the one that was specified
    if is_windows():
        return '\\\\.\\' + args.port.upper()

    if args.port is None:
        return get_default_edl_device()
    else:
        return args.port


def get_default_edl_device():
    serial_devices = glob.glob('/sys/bus/usb-serial/devices/*')
    edl_device = None
    for device in serial_devices:
        basedir = os.path.dirname(os.path.realpath(device))
        uevent_path = os.path.join(basedir, 'uevent')
        ids = get_vendor_and_product_ids(uevent_path)
        if ids[0] == '5c6' and ids[1] == '9008':
            edl_device = device
            break
    return None if edl_device is None else os.path.join(os.sep, 'dev', os.path.basename(edl_device))


def get_firehose_programmer():
    # Return the Firehose programmer from the current QFIL package
    firehose_program = glob.glob('prog*firehose*.elf')
    if len(firehose_program) != 1:
        raise RuntimeError('Found zero or multiple firehose programs')
    return firehose_program[0]


def get_storage_type():
    # Detect the storage type from the name of the Firehose programmmer
    firehose_program = get_firehose_programmer()
    if firehose_program[0].lower().find('emmc') != -1:
        storage_type = 'eMMC'
    else:
        storage_type = 'ufs'
    return storage_type


def get_rawprogram_xmls():
    # Return a list of rawprogram XML files from the current QFIL package
    raw_xml_files = glob.glob('rawprogram[0-9]_NO_SPARSE.xml' if args.mini else 'rawprogram[0-9].xml')
    raw_xml_files.sort()
    return raw_xml_files


def get_patch_xmls():
    # Return a list of patch XML files from the current QFIL packahe
    patch_xml_files = glob.glob('patch*.xml')
    patch_xml_files.sort()
    return patch_xml_files


def get_boot_lun():
    # Detect boot partition from the rawprogram XML files by looking for
    # the attribute 'physical_partition_number' of the 'xbl' or 'xbl_a'
    rawprograms = get_rawprogram_xmls()
    xbl = ['xbl', 'xbl_a']
    physical_partition_number = None
    for xml in rawprograms:
        with open(xml, 'r') as xml_file:
            xml_root = ET.parse(xml_file)
            xml_iter = xml_root.iter('program')
            for xml_element in xml_iter:
                label = xml_element.attrib.get('label')
                if label in xbl:
                    partition_number = xml_element.attrib.get('physical_partition_number')
                    if partition_number is not None and partition_number != '':
                        physical_partition_number = partition_number
                        break
        xml_file.close()
    return physical_partition_number


def kick_start():
    # Load Firehose programmer
    edl_device = get_edl_device()
    if edl_device is None:
        raise RuntimeError('Unable to find any device that is in EDL mode')

    if is_windows():
        cmd = [os.path.join(args.qcpath, 'bin', 'QSaharaServer.exe')]
    else:
        cmd = ['sudo', './kickstart']

    cmd.extend(['-p', edl_device, '-s', '13:' + get_firehose_programmer()])
    subprocess.check_call(cmd)


def qfil(secure, reset_only):
    """
    This function launch the Firehose loader to either flash or reset a device,
    or both based on the following parameters

    secure - true for sending per-packet digest for secure devices
    reset_only - Only reset the device (skip flashing) if this is true
    """

    # Detect the port for EDL device
    edl_device = get_edl_device()
    if edl_device is None:
        raise RuntimeError('Unable to find any device that is in EDL mode')

    # Flash QFIL package using fh_loader
    if is_windows():
        cmd = [os.path.join(args.qcpath, 'bin', 'fh_loader.exe')]
    else:
        cmd = ['sudo', './fh_loader']

    storage_type = get_storage_type()
    cmd.extend([
        '--port=' + edl_device,
        '--noprompt', '--showpercentagecomplete',
        '--memoryname=' + storage_type
    ])

    if secure:
        # For secure QFIL to work on Windows, the option --zlpawarehost is required.
        # Qualcomm document doesn't say much what it is, only states that it needs
        # to be enabled.
        config = {
            'size': 'Mini' if args.mini else 'Full',
            'zlp': 'Zlp' if is_windows() else ''
        }
        digest_options = [
            '--signeddigests=DigestsToSign.bin.mbn'.format(**config),
            '--chaineddigests=ChainedTableOfDigests.bin'.format(**config)
        ]
        cmd.extend(digest_options)

    if not reset_only:
        cmd.extend([
            '--sendxml=' + ','.join(get_rawprogram_xmls()) + ',' + ','.join(get_patch_xmls())
        ])
        boot_lun = get_boot_lun()
        if boot_lun is not None:
            cmd.extend(['--setactivepartition=' + boot_lun])
        elif storage_type == 'ufs':
            print('Warning: couldn\'t detect boot lun')

    cmd.extend(['--reset', '--zlpawarehost=' + ('1' if is_windows() else '0')])
    cmd.extend(['--maxpayloadsizeinbytes=8192'])

    try:
        subprocess.check_call(cmd)
        success = True
    except subprocess.CalledProcessError as e:
        success = False
        print(e.output)

    return success


def secure_qfil():
    return qfil(True, False)


def insecure_qfil():
    return qfil(False, False)


def reset_firehose():
    return qfil(False, True)


if __name__ == '__main__':
    if platform.system() == 'Darwin':
        raise RuntimeError('Mac OS is not currently supported, please use Windows or Linux.')

    parser = argparse.ArgumentParser(description='QFIL package updater')

    # Optional arguments
    parser.add_argument('-m', '--mini', action='store_true', help='Enable mini QFIL (skip flashing system and userdata)')
    parser.add_argument('-s', '--skip-firehose', action='store_true', help='Skip loading the Firehose programmer')

    # Options that are mutually exclusive
    flavor_group = parser.add_mutually_exclusive_group()
    flavor_group.add_argument('-x', '--secure', action='store_true', help='Enable secure QFIL')
    flavor_group.add_argument('-i', '--insecure', action='store_true', help='Disable secure QFIL')

    if is_windows():
        parser.add_argument('-p', '--port', help='COM port, e.g. COM1 (Windows only)', required=True)
        parser.add_argument('-q', '--qcpath', help='QPST path (Windows only)', default='c:\Program Files (x86)\Qualcomm\QPST')
    else:
        parser.add_argument('-p', '--port', help='select device, e.g. /dev/ttyUSB0 (Linux only)')

    args = parser.parse_args()

    cwd = os.getcwd()
    os.chdir(os.path.dirname(os.path.realpath(sys.argv[0])))

    if not args.skip_firehose:
        kick_start()

    if args.secure:
        secure_qfil()
    elif args.insecure:
        insecure_qfil()
    else:
        # Try secure QFIL first
        if not secure_qfil():
            # If secure QFIL failed, reset Firehose and try insecure next
            reset_firehose()
            insecure_qfil()

    os.chdir(cwd)
