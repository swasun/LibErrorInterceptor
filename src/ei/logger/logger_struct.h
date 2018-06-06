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
 *  @file      logger_struct.h
 *  @brief     Logger structure that contains the context of the log trace.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 *  @see       logger.h
 */

#ifndef ERRORINTERCEPTOR_LOGGER_STRUCT_H
#define ERRORINTERCEPTOR_LOGGER_STRUCT_H

#include <ei/bool.h>
#include <ei/thread/thread_mutex.h>

#include <stdio.h>

typedef enum {
    ERRORINTERCEPTOR_LOG_TRACE = 0,
    ERRORINTERCEPTOR_LOG_DEBUG,
    ERRORINTERCEPTOR_LOG_INFO,
    ERRORINTERCEPTOR_LOG_WARNING,
    ERRORINTERCEPTOR_LOG_ERROR,
    ERRORINTERCEPTOR_LOG_FATAL
} ei_logger_type;

typedef struct {
    int print_level, file_level;
    bool colored;
    bool details;
    bool padding;
    bool message_color_as_level_color;
    FILE *fp;
    ei_thread_mutex *mutex;
    char **level_colors;
    char *message_color;
} ei_logger;

#endif
