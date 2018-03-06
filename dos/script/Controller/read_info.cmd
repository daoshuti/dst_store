@echo off
set /p COM=Pleaset input COM number:
download_no_reset -p %COM% hex LLALM03_Controller_T12C0131_prod_test_580.hex || goto err
echo =====================================================
echo [SN]
prodtest -p %COM% read_SN
echo =====================================================
echo [PSN]
prodtest -p %COM% read_PSN
echo =====================================================
echo [Software Version]
prodtest -p %COM% read_swversion
echo =====================================================
echo [TouchPad Firmware Version]
prodtest -p %COM% read_TP_version
echo =====================================================
echo [Hardware Information]
prodtest -p %COM% read_device_info
echo =====================================================
echo [Buletooth MAC Address]
prodtest -p %COM% otp rd_bdaddr
echo.
echo.
echo.
pause

:err
echo =====================================================
echo Download FAIL!
echo =====================================================
pause