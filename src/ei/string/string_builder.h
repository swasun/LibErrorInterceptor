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
 *  @file      string_builder.h
 *  @brief     A string builder is a stream of string use to concatenate easily
 *             several types into a single string.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_STRING_BUILDER_H
#define ERRORINTERCEPTOR_STRING_BUILDER_H

#include <ei/bool.h>

#include <stddef.h>

typedef struct {
    char *data;
    size_t max_size;
    size_t position;
} ei_string_builder;

ei_string_builder *ei_string_builder_create();

ei_string_builder *ei_string_builder_create_size(size_t max_size);

bool ei_string_builder_append(ei_string_builder *s, char *data, size_t data_len);

bool ei_string_builder_append_variadic(ei_string_builder *s, const char *format, ...);

void ei_string_builder_clean_up(ei_string_builder *s);

void ei_string_builder_destroy(ei_string_builder *s);

char *ei_string_builder_get_data(ei_string_builder *s);

size_t ei_string_builder_get_position(ei_string_builder *s);

#endif
