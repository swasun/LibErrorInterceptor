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

#include <ei/string/string_builder.h>
#include <ei/alloc.h>
#include <ei/check_parameter.h>

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>

ei_string_builder *ei_string_builder_create() {
    return ei_string_builder_create_size(1);
}

ei_string_builder *ei_string_builder_create_size(size_t max_size) {
    ei_string_builder *s;

    ei_check_parameter_or_return(max_size > 0);

    ei_safe_alloc(s, ei_string_builder, 1);

    ei_safe_alloc_or_goto(s->data, char, max_size + 1, clean_up);

    memset(s->data, 0, max_size);
    s->max_size = max_size;
    s->position = 0;

    return s;

clean_up:
    ei_string_builder_destroy(s);
    return NULL;
}

bool ei_string_builder_append(ei_string_builder *s, char *data, size_t data_len) {
    ei_check_parameter_or_return(s);
    ei_check_parameter_or_return(data);
    ei_check_parameter_or_return(data_len > 0 && data_len != 18446744073709551615UL);

    if ((data_len + s->position) > s->max_size) {
        ei_safe_realloc(s->data, char, s->max_size, data_len + 1);
        s->max_size += data_len + 1;
    }

    memcpy(s->data + s->position, data, data_len);

    s->position += data_len;

    return true;
}

bool ei_string_builder_append_variadic(ei_string_builder *s, const char *format, ...) {
    bool result;
    va_list args;
    char *buffer;

    result = false;
    buffer = NULL;

    ei_safe_alloc(buffer, char, 8192);

    va_start(args, format);
    vsnprintf(buffer, 8192, format, args);
    va_end(args);

    if (!(result = ei_string_builder_append(s, buffer, strlen(buffer)))) {
        ei_stacktrace_push_msg("Failed to append concatenated args");
    }

    ei_safe_free(buffer);

    return result;
}

void ei_string_builder_clean_up(ei_string_builder *s) {
    if (!s) {
        return;
    }

    if (!s->data) {
        return;
    }

    memset(s->data, 0, s->max_size);
    s->position = 0;
}

void ei_string_builder_destroy(ei_string_builder *s) {
    if (!s) {
        return;
    }

    ei_safe_free(s->data);
    ei_safe_free(s);
}

char *ei_string_builder_get_data(ei_string_builder *s) {
    if (!s || !s->data) {
        return NULL;
    }

    return s->data;
}

size_t ei_string_builder_get_position(ei_string_builder *s) {
    if (!s) {
        return -1;
    }

    return s->position;
}
