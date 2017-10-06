/**
 ****************************************************************************************
 *
 * @file commands.c
 *
 * @brief Commands source code file.
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
#include <stdint.h>

#include "uart_down.h"

extern int g_com_port_number;

#define LOG_EN 0
int down_bin_cmd_handler(int argc, char **argv)
{
    FILE * fp = NULL;
    int file_size = 0, i = 0, recv_len = 0;
    char tmp, *ptr = NULL, crc = 0, recv = 0, send_buff[3] = {0};

    if (!(argc == 2))
    {
        fprintf(stderr, "[Download] argc error!");
        return -1;
    }

    //Open file
    fp = fopen(argv[1], "rb");
    if(fp == NULL)
    {
        fprintf(stderr, "[Download] Open %s failed!\nerrno is %d", argv[1], errno);
        return -1;
    }

    //Get file size
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    printf("[Download] File size = %d Bytes\r\n", file_size);
    ptr = malloc(file_size + 3);
    rewind(fp);

    //CRC
    while(1)
    {
        tmp = fgetc(fp);
        if(tmp == EOF)// Is EOF
        {
            if(feof(fp) != 0)
                break;
        }
        crc ^= tmp;
    }
    crc ^= 0x01;
    crc ^= 0x02;
    crc ^= 0x04;

    //wait reset signal
    if(uart_init(g_com_port_number,57600))
    {
        fprintf(stderr, "[Download] Open serial com%d failed!", g_com_port_number);
        return -1;
    }

    //Auto reset v190 controller
    uart_set_rts();//low -> reset board
    Sleep(1000);
    uart_reset_rts();//high -> release board

    printf("[Download] Please reset board.\r\n");
    for(i = 0; i < 100; i++)//retry 100 time
    {
        //Is reset
        recv_len = uart_recv(&recv, sizeof(char));
        if(recv_len == 0)
        {
            printf("[Download] Timeout!\r\n");
            return -1;
        }
        if(recv == 0x11)
        {
            uart_recv(&recv, sizeof(char));
            if(recv == 0x02)
                break;
            #if LOG_EN
            else
                printf("[Download] Don't reset signal! recv : 0x%02x. Retry %d time.\r\n", recv, i);
            #endif
        }
        #if LOG_EN
        else
            printf("[Download] Don't reset signal! recv : 0x%02x. Retry %d time.\r\n", recv, i);
        #endif
    }
    printf("[Download] Reset\r\n");

    //send ack and file size
    send_buff[0] = 0x01;
    send_buff[1] = (((file_size+3) & 0x00ff) >> 0);//LSB
    send_buff[2] = (((file_size+3) & 0xff00) >> 8);//MSB
    uart_send(send_buff, 3 * sizeof(char));

    //wait ack
    uart_recv(&recv, sizeof(char));
    if(recv != 0x06)
    {
        fprintf(stderr, "[Download] ACK Failed!");
        return -1;
    }

    //send software
    rewind(fp);
    fread(ptr, sizeof(char), file_size, fp);
    ptr[file_size+0] = 0x01;
    ptr[file_size+1] = 0x02;
    ptr[file_size+2] = 0x04;
    uart_send(ptr, file_size + 3);

    //check CRC
    uart_recv(&recv, sizeof(char));
    if(recv != crc)
    {
        fprintf(stderr, "[Download] CRC Failed!");
        return -1;
    }
    else
        printf("[Download] CRC is right.\r\n");

    //send ack
    send_buff[0] = 0x06;
    uart_send(send_buff, 1 * sizeof(char));

    fclose(fp);
    free(ptr);
    uart_close();
    printf("[Download] Successfully downloaded firmware file to the board.\r\n");

    return 0;
}

int parse_hex_file(char *ptr, const char * hex_file_path);

int down_hex_cmd_handler(int argc, char **argv)
{
    int file_size = 0, i = 0, recv_len = 0;
    char *ptr = NULL, crc = 0, recv = 0, send_buff[3] = {0};
    if (!(argc == 2))
    {
        fprintf(stderr, "[Download] argc error!");
        return -1;
    }

    //Parse Hex File
    ptr = malloc(0x10000 * sizeof(char));//64Kbytes
    memset(ptr,0,0x10000);
    if((file_size = parse_hex_file(ptr, argv[1]))< 0)
    {
        fprintf(stderr, "[Download] Parse Hex Failed!");
    }
    printf("[Download] File size = %d Bytes\r\n", file_size);

    //CRC
    for(i = 0; i < file_size; i++)
        crc ^= ptr[i];
    crc ^= 0x01;
    crc ^= 0x02;
    crc ^= 0x04;

    //wait reset signal
    if(uart_init(g_com_port_number,57600))
    {
        fprintf(stderr, "[Download] Open serial com%d failed!", g_com_port_number);
        return -1;
    }

    //Auto reset v190 controller
    uart_set_rts();//low -> reset board
    Sleep(1000);
    uart_reset_rts();//high -> release board

    printf("[Download] Please reset board.\r\n");
    for(i = 0; i < 100; i++)//retry 100 time
    {
        //Is reset
        recv_len = uart_recv(&recv, sizeof(char));
        if(recv_len == 0)
        {
            printf("[Download] Timeout!\r\n");
            return -1;
        }
        if(recv == 0x11)
        {
            uart_recv(&recv, sizeof(char));
            if(recv == 0x02)
                break;
            #if LOG_EN
            else
                printf("[Download] Don't reset signal! recv : 0x%02x. Retry %d time.\r\n", recv, i);
            #endif
        }
        #if LOG_EN
        else
            printf("[Download] Don't reset signal! recv : 0x%02x. Retry %d time.\r\n", recv, i);
        #endif
    }
    printf("[Download] Reset\r\n");

    //send ack and file size
    send_buff[0] = 0x01;
    send_buff[1] = (((file_size+3) & 0x00ff) >> 0);//LSB
    send_buff[2] = (((file_size+3) & 0xff00) >> 8);//MSB
    uart_send(send_buff, 3 * sizeof(char));

    //wait ack
    uart_recv(&recv, sizeof(char));
    if(recv != 0x06)
    {
        fprintf(stderr, "[Download] ACK Failed!");
        return -1;
    }

    //send software
    ptr[file_size+0] = 0x01;
    ptr[file_size+1] = 0x02;
    ptr[file_size+2] = 0x04;
    uart_send(ptr, file_size + 3);

    //check CRC
    uart_recv(&recv, sizeof(char));
    if(recv != crc)
    {
        fprintf(stderr, "[Download] CRC Failed!");
        return -1;
    }
    else
        printf("[Download] CRC is right.\r\n");

    //send ack
    send_buff[0] = 0x06;
    uart_send(send_buff, 1 * sizeof(char));

    free(ptr);
    uart_close();
    printf("[Download] Successfully downloaded firmware file to the board.\r\n");
    return 0;
}

int parse_hex_file(char *ptr, const char * hex_file_path)
{
    int i;
    FILE * fp = NULL;
    char tmp, buff[64], *cur_ptr;
    int code_data;
    unsigned int nbytes, type, addr, file_size = 0;

    if(ptr == NULL)
    {
        fprintf(stderr, "[Parse Hex] ptr is NULL!");
        return -1;
    }
    else
        cur_ptr = ptr;

    //Open file
    fp = fopen(hex_file_path, "rb");
    if(fp == NULL)
    {
        fprintf(stderr, "[Parse Hex] Open %s failed!\nerrno is %d", hex_file_path, errno);
        return -1;
    }

    //Parse Hex File
    while(1)
    {
        tmp = fgetc(fp);
        if(tmp == ':')
        {
            fread(buff, sizeof(char), 8, fp);
            if(sscanf(buff,"%02x%04x%02x",&nbytes,&addr,&type) != 3)
            {
                fprintf(stderr,"[Parse Hex] sscanf failed!");
                return -1;
            }
            if(type == 0x00)//data
            {
                file_size = addr + nbytes;
                cur_ptr = ptr + addr;
                fread(buff, sizeof(char), nbytes*2 + 2, fp);
                for(i = 0; i < nbytes; i++)
                {
                    if(sscanf(&buff[i*2],"%02x",&code_data) != 1)
                    {
                        fprintf(stderr,"[Parse Hex] sscanf failed!");
                        return -1;
                    }
                    *cur_ptr = (char)code_data;
                    cur_ptr++;
                }
            }
            else if (type == 0x01)//end
                break;
            else if (type == 0x04 || type == 0x05)
                continue;
            else
            {
                fprintf(stderr,"[Parse Hex] Parse failed!");
                return -1;
            }
        }
        else if (tmp == '\r' || tmp == '\n')
            continue;
        else if(tmp == EOF)// Is EOF
        {
            fprintf(stderr,"[Parse Hex] read EOF!");
            return -1;
        }
    }
    fclose(fp);
    return file_size;
}

