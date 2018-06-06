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
 *  @file      string_utility.h
 *  @brief     Utility functions for string manipulations.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_STRING_UTILITY_H
#define ERRORINTERCEPTOR_STRING_UTILITY_H

#include <ei/bool.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

void ei_remove_last_char(char *str);

bool ei_last_char_is(char *str, char c);

char *ei_strcat_variadic(const char *format, ...);

int ei_find_str_in_data(char *data, const char *query);

char *ei_get_file_name_from_path(char *path);

char *ei_get_file_extension(char *path);

char *ei_string_create_from(const char *str);

char *ei_string_create_from_bytes(unsigned char *bytes, size_t size);

char *ei_append_dump_string(char *data, size_t max);

bool ei_starts_with(const char *pre, const char *str);

int ei_last_index_of(const char *string, char target);

char *ei_string_reverse(char *string);

bool ei_int_to_string(int num, char *buffer, int radix);

bool ei_long_to_string(long num, char *buffer, int radix);

/**
 * Convert char * string to int out.
 * @param[in] string Input string to be converted.
 *
 * The format is the same as strtol,
 * except that the following are inconvertible:
 * - empty string
 * - leading whitespace
 * - any trailing characters that are not part of the number
 *   cannot be NULL.
 *
 * @param[out] out The converted int. Cannot be NULL.
 * @param[in] radix Base to interpret string in. Same range as strtol (2 to 36).
 * @return Indicates if the operation succeeded, or why it failed.
 */
bool ei_string_to_int(char *string, int *out, int radix);

bool ei_string_to_long(char *string, long *out, int radix);

int ei_digit(char c, int radix);

/**
 * Returns a string that is a ei_substring of this string. The
 * ei_substring begins at the specified {@code begin_index} and
 * extends to the character at index {@code end_index - 1}.
 * Thus the length of the ei_substring is {@code end_index-begin_index}.
 *
 * Examples:
 * "hamburger".ei_substring(4, 8) returns "urge"
 * "smiles".ei_substring(1, 5) returns "mile"
 *
 * @param      begin_index   the beginning index, inclusive.
 * @param      end_index     the ending index, exclusive.
 * @return     the specified ei_substring.
 */
char *ei_substring(char *string, int begin_index, int end_index);

char *ei_get_until_symbol(char *str, int begin, char symbol, int *end);

char *ei_trim_whitespace(char *str);

#endif
