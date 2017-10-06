/**
 ****************************************************************************************
 *
 * @file main.c
 *
 * @brief Main source code file.
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

#include <stdlib.h>
#include <stdio.h>

#include "getopt.h"
#include "commands.h"
#include "uart_down.h"


//software version
#define SW_VERSION                  "v_1.1.0"
//commands
#define CMD__DOWN_HEX               "hex"
#define CMD__DOWN_BIN               "bin"

typedef int (*cmd_handler_t) (int argc, char **argv);

typedef struct {
    char cmd_name[64];
    cmd_handler_t cmd_handler;
} cmd_t;

/* global */
cmd_t cmd_table[] = {
    { CMD__DOWN_HEX                 , down_hex_cmd_handler},
    { CMD__DOWN_BIN                 , down_bin_cmd_handler},

    { "",0}
};

int g_com_port_number;

/* utils*/
void print_usage(void);
long parse_number(int *return_status, const char * str);


/* main */
int main(int argc, char **argv)
{
    int help_option = 0;
    int com_port_option = 0;
    int kk = 0;
    cmd_t *cmd = NULL;
    int rc;
    int opt;
    int cmd_argc;
    char ** cmd_argv;

    __progname = argv[0]; // used by getopt

    // parse command line switches
    while( ( opt = getopt( argc, argv, "hvp:" ) )!= -1 )  
    {
        switch( opt ) 
        {
        case 'h':
            print_usage();
            exit(SC_NO_ERROR);
            break;
        case 'p':
            {
                int return_status;
                long com_port_number = 0;

                com_port_number = parse_number(&return_status, optarg);
                if(return_status !=0 )
                {
                    fprintf(stderr, "Illegal com port number in -p option \n");
                    exit(SC_INVALID_COM_PORT_NUMBER);
                }
                com_port_option = 1;
                g_com_port_number = com_port_number;
            }
            break;
        case 'v':
            printf("%s\n",SW_VERSION);
            exit(SC_NO_ERROR);
            break;
        default :
            break;
        }
    }

    if (help_option)
    {
        print_usage();
        exit(SC_NO_ERROR);
    }

    // remaining arguments are interpreted as
    //   <cmd> <cmd_arg_1> <cmd_arg_2>  ... <cmd_arg_n>
    // and the following will hold:
    //    cmd_argc = 1 + n
    //    cmd_argv[0] = <cmd> 
    //    cmd_argv[1] = <cmd_arg_1>
    //    cmd_argv[2] = <cmd_arg_2>
    //    ...
    //    cmd_argv[n] = <cmd_arg_n>

    cmd_argc = argc - optind;
    cmd_argv = argv + optind;

    //
    // check if a command was specified 
    //
    if (cmd_argc == 0 )
    {
        fprintf(stderr, "No command specified. \n");
        print_usage();
        exit(SC_MISSING_COMMAND);
    }

    // search for command handler - cmd_argv[0] contains the command name 
    for (kk = 0; cmd_table[kk].cmd_name[0] != 0; kk++)
    {
        if ( 0 == strcmp(cmd_argv[0], cmd_table[kk].cmd_name) )
        {
            cmd = &cmd_table[kk];
            break;
        }
    }

    // if no command handler was found
    if (cmd == NULL)
    {
        fprintf(stderr, "Invalid command: \"%s\"\n", cmd_argv[0]);
        exit(SC_INVALID_COMMAND);
    }

    // all commands require a COM port
    if (!com_port_option) 
    {
        fprintf(stderr, "Option -p is required. \n");
        print_usage();
        exit(SC_COM_PORT_NOT_SPECIFIED);
    }

    //
    // execute command
    //
    rc = cmd->cmd_handler(cmd_argc, cmd_argv);

    return rc;

}

void print_usage(void)
{
    printf("Usage: \n");

    printf("\tdownload -h \n");

    printf("\tdownload -p <COM> bin <FILE_PATH> \n");
    printf("\tdownload -p <COM> hex <FILE_PATH> \n");

    printf("\tdownload -v \n");
}

long parse_number(int *return_status, const char * str)
{
    long result;
    char *endptr;

    *return_status = 0;

    result = strtol(str, &endptr, 10);

    if (endptr[0])
        *return_status = 1;

    if (errno)
        *return_status = 1;

    return result;
}
