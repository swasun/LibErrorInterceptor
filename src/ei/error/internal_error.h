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
 *  @file      internal_error.h
 *  @brief     Internal error provides a set of common errors.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_INTERNAL_ERROR_H
#define ERRORINTERCEPTOR_INTERNAL_ERROR_H

#include <ei/error/error.h>

#include <stdio.h>

typedef enum {
	ERRORINTERCEPTOR_SUCCESS,
	ERRORINTERCEPTOR_NO_SUCH_MEMORY,
	ERRORINTERCEPTOR_FILE_NOT_FOUND,
    ERRORINTERCEPTOR_INVALID_PARAMETER,
    ERRORINTERCEPTOR_NO_INTERNET_CONNECTION,
	ERRORINTERCEPTOR_UNKNOWN_ERROR
} ei_internal_error_type;

char *ei_internal_error_get_description(ei_internal_error_type type);

char *ei_internal_error_to_string(ei_error *e);

void ei_internal_error_print(ei_error *e, FILE *out);

#endif
