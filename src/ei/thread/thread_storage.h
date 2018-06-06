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
 *  @file      thread_storage.h
 *  @brief     Singleton module to retreive an object per thread.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_THREAD_STORAGE_H
#define ERRORINTERCEPTOR_THREAD_STORAGE_H

#include <ei/bool.h>
#include <ei/stacktrace/stacktrace_struct.h>

bool ei_thread_storage_init();

void ei_thread_storage_uninit();

bool ei_thread_storage_append_to_be_deleted_data(void *data);

ei_stacktrace *ei_thread_storage_get_stacktrace();

ei_stacktrace **ei_thread_storage_get_all_stacktrace(int *number);

ei_stacktrace *ei_thread_storage_get_stacktrace_from_thread_id(long ei_thread_id);

bool ei_thread_storage_set_char_data(char *data);

char *ei_thread_storage_get_char_data();

bool ei_thread_storage_set_int_data(int data);

int ei_thread_storage_get_int_data();

#endif
