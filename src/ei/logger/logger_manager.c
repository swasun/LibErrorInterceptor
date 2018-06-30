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

#include <ei/logger/logger_manager.h>
#include <ei/thread/thread_storage.h>
#include <ei/alloc.h>

static ei_logger *ei_global_log = NULL;

bool ei_logger_manager_init() {
	ei_global_log = ei_logger_create();
    ei_logger_set_details(ei_global_log, false);
    return true;
}

void ei_logger_manager_uninit() {
    ei_logger_destroy(ei_global_log);
}

ei_logger *ei_logger_manager_get_logger() {
    return ei_global_log;
}
