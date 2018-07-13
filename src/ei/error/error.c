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

#include <ei/error/error.h>

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define ERROR_MAX_SIZE 5192

ei_error *ei_error_create(char *func_name, char *file_name, int line_number, char *description) {
    ei_error *e;
	int length;
	char *final_file_name;
	char slash;

	#ifdef __linux__
        slash = '/';
    #elif defined(_WIN32) || defined(_WIN64)
        slash = '\\';
    #else
        #error "OS not supported"
    #endif

    e = (ei_error *)malloc(sizeof(ei_error));

	length = strlen(description) + 1;
	e->description = (char*)malloc(length * sizeof(char));
	strcpy(e->description, description);

	length = strlen(func_name) + 1;
	e->func_name = (char*)malloc(length * sizeof(char));
	strcpy(e->func_name, func_name);

	if (strrchr(file_name, slash)) {
		final_file_name = strrchr(file_name, slash) + 1;
	} else {
		final_file_name = file_name;
	}

	length = strlen(final_file_name) + 1;
	e->file_name = (char*)malloc(length * sizeof(char));
	strcpy(e->file_name, final_file_name);

	e->line_number = line_number;
	e->is_main_error = false;

	return e;
}

ei_error *ei_error_create_variadic(char *func_name, char *file_name, int line_number, const char *format, ...) {
    ei_error *e;
	int length;
	char *final_file_name;
	char slash;
    va_list args;

	#ifdef __linux__
        slash = '/';
    #elif defined(_WIN32) || defined(_WIN64)
        slash = '\\';
    #else
        #error "OS not supported"
    #endif

    e = (ei_error *)malloc(sizeof(ei_error));

    va_start(args, format);
    length = ERROR_MAX_SIZE;
	e->description = (char*)malloc(length * sizeof(char));
    vsnprintf(e->description, ERROR_MAX_SIZE, format, args);
    va_end(args);

	length = strlen(func_name) + 1;
	e->func_name = (char*)malloc(length * sizeof(char));
	strcpy(e->func_name, func_name);

	if (strrchr(file_name, slash)) {
		final_file_name = strrchr(file_name, slash) + 1;
	} else {
		final_file_name = file_name;
	}

	length = strlen(final_file_name) + 1;
	e->file_name = (char*)malloc(length * sizeof(char));
	strcpy(e->file_name, final_file_name);

	e->line_number = line_number;
	e->is_main_error = false;

	return e;
}

void ei_error_clean_up(ei_error *e) {
    if (e) {
		if (e->description) {
			free((void *)e->description);
            e->description = NULL;
		}

		if (e->func_name) {
			free((void *)e->func_name);
            e->func_name = NULL;
		}

		if (e->file_name) {
			free((void *)e->file_name);
            e->file_name = NULL;
		}
	}
}

void ei_error_destroy(ei_error *e) {
	if (e) {
		if (e->description) {
			free((void *)e->description);
		}

		if (e->func_name) {
			free((void *)e->func_name);
		}

		if (e->file_name) {
			free((void *)e->file_name);
		}

		free((void *)e);
		e = NULL;
	}
}

bool ei_error_equals(ei_error *e1, ei_error *e2) {
	return e1 && e2 && ((e1 == e2) || (
		strcmp(e1->description, e2->description) == 0 &&
		strcmp(e1->func_name, e2->func_name) == 0 &&
		strcmp(e1->file_name, e2->file_name) == 0 &&
		e1->line_number == e2->line_number
	));
}
