/**********************************************************************************
 * Copyright (C) 2018 by Charly Lamothe                                           *
 *                                                                                *
 * This file is part of LibErrorInterceptor.                                      *
 *                                                                                *
 *   LibErrorInterceptor is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by         *
 *   the Free Software Foundation, either version 3 of the License, or            *
 *   (at your option) any later version.                                          *
 *                                                                                *
 *   LibErrorInterceptor is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 *   GNU General Public License for more details.                                 *
 *                                                                                *
 *   You should have received a copy of the GNU General Public License            *
 *   along with LibErrorInterceptor.  If not, see <http://www.gnu.org/licenses/>. *
 **********************************************************************************/

/**
 *  @file      error.h
 *  @brief     Error module to create generic error.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_ERROR_H
#define ERRORINTERCEPTOR_ERROR_H

#include <ei/bool.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

#include <stdarg.h>

/**
 * Error structure that describe an error context.
 */
typedef struct {
    char *description;
    char *func_name;
    char *file_name;
    int line_number;
    bool is_main_error;
} ei_error;

#if defined(_WIN32) || defined(_WIN64)
    #define ei_format_error(error_buffer, code) \
        error_buffer = NULL; \
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, \
        NULL, \
        code, \
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), \
        (LPTSTR)&error_buffer, \
        0, \
        NULL); \

    #define ei_get_last_werror(error_buffer) ei_format_error(error_buffer, GetLastError())

    #define ei_get_last_wsa_error(error_buffer) ei_format_error(error_buffer, WSAGetLastError())
#endif

ei_error *ei_error_create(char *func_name, char *file_name, int line_number, char *description);

ei_error *ei_error_create_variadic(char *func_name, char *file_name, int line_number, const char *format, ...);

void ei_error_clean_up(ei_error *e);

void ei_error_destroy(ei_error *e);

bool ei_error_equals(ei_error *e1, ei_error *e2);

#endif
