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

#include <ei/init.h>
#include <ei/thread/thread_storage.h>
#include <ei/bool.h>
#include <ei/logger/logger_manager.h>

static bool ei_thread_storage_initialized = false;

int ei_init() {
	if (!ei_thread_storage_initialized) {
		ei_thread_storage_initialized = ei_thread_storage_init();
	}

	ei_logger_manager_init();

	return ei_thread_storage_initialized;
}

void ei_uninit() {
	ei_logger_manager_uninit();

	if (ei_thread_storage_initialized) {
		ei_thread_storage_uninit();
	}
}
