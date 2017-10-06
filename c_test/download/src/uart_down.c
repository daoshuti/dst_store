/**
 ****************************************************************************************
 *
 * @file uart_down.c
 *
 * @brief uart source code file.
 *
 * Copyright (C) 2017. Longcheer Ltd, unpublished work. This computer
 * program includes Confidential, Proprietary Information and is a Trade Secret of
 * Longcheer Ltd.  All use, disclosure, and/or reproduction is prohibited
 * unless authorized in writing. All Rights Reserved.
 *
 * <wanghan@longcheer.com> and contributors.
 *
 ****************************************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "uart_down.h"

static HANDLE down_hComPortHandle = NULL;
static OVERLAPPED down_ovlRd,down_ovlWr;

/*
 ****************************************************************************************
 * @brief Write message to UART.
 *  @param[in] send_buff       Pointer to message's data.
 *  @param[in] send_size       message's size.
 *
 * @return -1 (failed) / send buffer size (success).
 ****************************************************************************************
 */
int uart_send(char *send_buff, int buff_size)
{
    unsigned long dwWritten;

    down_ovlWr.Offset     = 0;
    down_ovlWr.OffsetHigh = 0;
    ResetEvent(down_ovlWr.hEvent);

    WriteFile(down_hComPortHandle, send_buff, buff_size, &dwWritten, &down_ovlWr);

    return (int)dwWritten;
}

/*
 ****************************************************************************************
 * @brief recv UART
 *
 *  @param[in] recv_buff      Message's data.
 *  @param[in] buff_size      Message's size.
 *
 * @return -1 (failed) / recv buffer size (success).
 ****************************************************************************************
 */
int uart_recv(char *recv_buff, int buff_size)
{
    unsigned long dwBytesRead;

    down_ovlRd.Offset     = 0;
    down_ovlRd.OffsetHigh = 0;
    ResetEvent(down_ovlRd.hEvent);

    ReadFile(down_hComPortHandle, recv_buff, buff_size, &dwBytesRead, &down_ovlRd);

    return (int)dwBytesRead;
}

/*
 ****************************************************************************************
 * @brief UART Close
 *
 * @return void.
 ****************************************************************************************
 */
void uart_close(void)
{
    CloseHandle(down_hComPortHandle);
    fprintf(stderr, "[UART info] Close UART success\r\n");
}
//set RTS
void uart_set_rts(void)
{
	EscapeCommFunction(down_hComPortHandle,SETRTS);
}
// reset RTS
void uart_reset_rts(void)
{
	EscapeCommFunction(down_hComPortHandle,CLRRTS);
}

/*
 ****************************************************************************************
 * @brief Init UART iface.
 *
 *  @param[in] port			COM prot number.
 *  @param[in] baudrate		Baud rate.
 *
 * @return -1 on failure / 0 on success.
 ****************************************************************************************
 */
int uart_init(int port, int baudrate)
{
    DCB dcb;
    DWORD dwErrorCode;
    BOOL fSuccess;
    COMSTAT stat;
    DWORD error;
    COMMTIMEOUTS commtimeouts;
    char CPName[64];

    sprintf(CPName, "\\\\.\\COM%d", port);

    fprintf(stderr, "[UART info] Connecting to %s\n", &CPName[4]);

    down_ovlRd.hEvent = CreateEvent( NULL,FALSE,FALSE,NULL );
    down_ovlWr.hEvent = CreateEvent( NULL,FALSE,FALSE,NULL );

    down_hComPortHandle = CreateFile(CPName,
            GENERIC_WRITE | GENERIC_READ,
            0, //FILE_SHARE_WRITE | FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            0,//0 (sync), FILE_FLAG_OVERLAPPED (overlapped)
            NULL );

    if(down_hComPortHandle == INVALID_HANDLE_VALUE)
    {
        dwErrorCode = GetLastError();
        fprintf(stderr, "[UART info] Failed to open %s! %lu\n", CPName,dwErrorCode);
        return -1;
    }

    ClearCommError( down_hComPortHandle, &error, &stat );

    memset(&dcb, 0x0, sizeof(DCB) );
    fSuccess = GetCommState(down_hComPortHandle, &dcb);
    if(!fSuccess)
    {
        fprintf(stderr, "[UART info] Failed to get DCB!\n");
        return -1;
    }

    // Fill in the DCB
    dcb.BaudRate = baudrate;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fBinary = 1;
    // disable all kind of flow control and error handling
    dcb.fOutxCtsFlow = 0;
    dcb.fOutxDsrFlow = 0;
    dcb.fRtsControl  = RTS_CONTROL_DISABLE;//RTS_CONTROL_ENABLE
    dcb.fDtrControl  = DTR_CONTROL_DISABLE;
    dcb.fInX         = 0;
    dcb.fOutX        = 0;
    dcb.fErrorChar   = 0;
    dcb.fNull        = 0;
    dcb.fAbortOnError = 0;

    fSuccess = SetCommState(down_hComPortHandle, &dcb);
    if(!fSuccess)
    {
        fprintf(stderr, "[UART info] Failed to set DCB!\n");
        return -1;
    }
    commtimeouts.ReadIntervalTimeout = 1000; 
    commtimeouts.ReadTotalTimeoutMultiplier = 0; 
    commtimeouts.ReadTotalTimeoutConstant = 0; 
    commtimeouts.WriteTotalTimeoutMultiplier = 0; 
    commtimeouts.WriteTotalTimeoutConstant = 0;

    fSuccess = SetCommTimeouts(down_hComPortHandle, &commtimeouts);

    fprintf(stderr, "[UART info] %s succesfully opened, baud rate %d\n", &CPName[4], baudrate);

    return 0;
}
