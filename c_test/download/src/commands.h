/**
 ****************************************************************************************
 *
 * @file commands.h
 *
 * @brief Commands header file.
 *
 * Copyright (C) 2015. Dialog Semiconductor Ltd, unpublished work. This computer
 * program includes Confidential, Proprietary Information and is a Trade Secret of
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited
 * unless authorized in writing. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */

#ifndef _COMMANDS_H_
#define _COMMANDS_H_

/* status codes */
#define SC_NO_ERROR                                 0
#define SC_MISSING_COMMAND                          1
#define SC_INVALID_COMMAND                          2
#define SC_WRONG_NUMBER_OF_ARGUMENTS                3
#define SC_INVALID_COM_PORT_NUMBER                  4
#define SC_COM_PORT_NOT_SPECIFIED                   5
#define SC_COM_PORT_INIT_ERROR                      6

/* command handlers */
int down_bin_cmd_handler(int argc, char **argv);
int down_hex_cmd_handler(int argc, char **argv);

#endif /* _COMMANDS_H_ */
