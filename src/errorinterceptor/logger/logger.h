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
 *  @file      logger.h
 *  @brief     Logger module handle different types of log message.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 *  @see       logger_struct.h
 */

#ifndef ERRORINTERCEPTOR_LOGGER_H
#define ERRORINTERCEPTOR_LOGGER_H

#include <errorinterceptor/bool.h>
#include <errorinterceptor/logger/logger_struct.h>
#include <errorinterceptor/logger/logger_manager.h>
#include <errorinterceptor/stacktrace/stacktrace_struct.h>
#include <errorinterceptor/thread/thread_storage.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

ei_logger *ei_logger_create();

void ei_logger_destroy(ei_logger *log);

void ei_logger_set_fp(ei_logger *log, FILE *fp);

void ei_logger_set_file_level(ei_logger *log, int level);

void ei_logger_set_print_level(ei_logger *log, int level);

int ei_logger_get_print_level(ei_logger *log);

int ei_logger_get_file_level(ei_logger *log);

void ei_logger_set_colored(ei_logger *log, bool enable);

void ei_logger_set_details(ei_logger *log, bool enable);

void ei_logger_set_padding(ei_logger *log, bool enable);

void ei_logger_set_message_color(ei_logger *log, const char *color);

void ei_logger_set_message_color_as_level_color(ei_logger *log, bool enable);

bool ei_logger_record(ei_logger *log, int level, const char *file, int line, const char *fmt, ...);

bool ei_logger_record_stacktrace(ei_logger *log, ei_stacktrace *stacktrace, const char *message, const char *file, int line);

#define ei_logger_stacktrace(message) ei_logger_record_stacktrace(ei_logger_manager_get_logger(), ei_thread_storage_get_stacktrace(), (const char *)message, (const char *)(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__)

#define ei_logger_trace(...) ei_logger_record(ei_logger_manager_get_logger(), ERRORINTERCEPTOR_LOG_TRACE, (const char *)(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__, __VA_ARGS__)

#define ei_logger_debug(...) ei_logger_record(ei_logger_manager_get_logger(), ERRORINTERCEPTOR_LOG_DEBUG, (const char *)(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__, __VA_ARGS__)

#define ei_logger_info(...) ei_logger_record(ei_logger_manager_get_logger(), ERRORINTERCEPTOR_LOG_INFO, (const char *)(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__, __VA_ARGS__)

#define ei_logger_warn(...) ei_logger_record(ei_logger_manager_get_logger(), ERRORINTERCEPTOR_LOG_WARNING,  (const char *)(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__, __VA_ARGS__)

#define ei_logger_error(...) ei_logger_record(ei_logger_manager_get_logger(), ERRORINTERCEPTOR_LOG_ERROR, (const char *)(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__, __VA_ARGS__)

#define ei_logger_fatal(...) ei_logger_record(ei_logger_manager_get_logger(), ERRORINTERCEPTOR_LOG_FATAL, (const char *)(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__, __VA_ARGS__)

FILE *ei_logger_get_fp(ei_logger *log);

#endif
