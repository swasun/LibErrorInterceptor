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

#include <ei/ei.h>

#include <stdlib.h>

int main() {
    ei_init();

    ei_logger_trace("Loading library...");

    ei_logger_debug("Variable value is %d", 58);

    ei_logger_info("User %s is now connected", "username");

    ei_logger_warn("Loading time is consequently longer");

    ei_logger_error("Invalid password");

    ei_logger_fatal("Out of memory");

    ei_uninit();

    return EXIT_SUCCESS;
}
