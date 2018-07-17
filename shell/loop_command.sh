#!/bin/bash
# Author: wanghan
# Created Time : 2018年07月17日 21:31:40
# File Name: loop_command.sh
# Description:

function loop_exe()
{
    local ex_count=0
    CMDLINE=$1
    while true ; do
        #command
        sleep 1
        echo The command is \"$CMDLINE\"
        ${CMDLINE}
        if [ $? == 0 ] ; then
            echo The command execute OK!
            break;
        else
            (( ex_count = ${ex_count} + 1 ))
            echo ERROR : The command execute fialed! ex_count = ${ex_count}.
        fi
    done
}


function main()
{
    echo --- Start ---
    loop_exe "echo This is command list:"
    loop_exe "repo init -u https://android.googlesource.com/platform/manifest"
    loop_exe "repo sync -j4"
    echo --- Done ---
}

main
