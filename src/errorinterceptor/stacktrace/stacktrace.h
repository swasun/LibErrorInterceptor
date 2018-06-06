/*******************************************************************************
 * Copyright (C) 2018 by Charly Lamothe                                        *
 *                                                                             *
 * This file is part of ErrorInterceptor.                                      *
 *                                                                             *
 *   ErrorInterceptor is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by      *
 *   the Free Software Foundation, either version 3 of the License, or         *
 *   (at your option) any later version.                                       *
 *                                                                             *
 *   ErrorInterceptor is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *   GNU General Public License for more details.                              *
 *                                                                             *
 *   You should have received a copy of the GNU General Public License         *
 *   along with ErrorInterceptor.  If not, see <http://www.gnu.org/licenses/>. *
 *******************************************************************************/

/**
 *  @file      stacktrace.h
 *  @brief     Stacktrace module to record error into ei_stacktrace struct.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_STRACKTRACE_H
#define ERRORINTERCEPTOR_STRACKTRACE_H

#include <errorinterceptor/error/error.h>
#include <errorinterceptor/error/internal_error.h>
#include <errorinterceptor/stacktrace/stacktrace_struct.h>
#include <errorinterceptor/bool.h>
#include <errorinterceptor/thread/thread_storage.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void ei_stacktrace_create(ei_stacktrace **stack);

void ei_stacktrace_destroy(ei_stacktrace *stack);

void push_to_stacktrace(ei_stacktrace *stack, ei_error *e);

char *ei_stacktrace_to_string(ei_stacktrace *stack);

void ei_stacktrace_print();

void ei_stacktrace_print_all();

void ei_stacktrace_print_fd_all(FILE *fd);

void ei_stacktrace_print_this(ei_stacktrace *stack);

void ei_stacktrace_print_fd(FILE *fd);

void ei_stacktrace_print_fd_this(ei_stacktrace *stack, FILE *fd);

char *ei_stacktrace_get_cause();

char *ei_stacktrace_get_cause_this(ei_stacktrace *stack);

bool ei_stacktrace_is_filled_this(ei_stacktrace *stack);

bool ei_stacktrace_is_filled();

void ei_stacktrace_clean_up();

#define ei_stacktrace_push_code(code) \
    char *description; \
    description = ei_internal_error_get_description(code); \
    push_to_stacktrace(ei_thread_storage_get_stacktrace(), ei_error_create((char *)__func__, __FILE__, __LINE__, description)); \
    free((void*)description); \

#define ei_stacktrace_push_errno() \
    char *description; \
    if (errno == 0) { \
        description = ei_internal_error_get_description(ERRORINTERCEPTOR_UNKNOWN_ERROR); \
        push_to_stacktrace(ei_thread_storage_get_stacktrace(), ei_error_create((char *)__func__, __FILE__, __LINE__, description)); \
        free((void*)description); \
    } else { \
        push_to_stacktrace(ei_thread_storage_get_stacktrace(), ei_error_create((char *)__func__, __FILE__, __LINE__, strerror(errno))); \
    } \

#define ei_stacktrace_push_msg(...) \
    push_to_stacktrace(ei_thread_storage_get_stacktrace(), ei_error_create_variadic((char *)__func__, __FILE__, __LINE__, __VA_ARGS__)); \

#endif
