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

bool foo(void *parameter) {
    if (!parameter) {
        ei_stacktrace_push_msg("Specified parameter is invalid");
        return false;
    }

    return true;
}

bool bar(void *parameter) {
    if (!foo(parameter)) {
        ei_stacktrace_push_msg("foo failed :(");
        return false;
    }

    return true;
}

/**
 * output:
 * bar failed ! (thread 140371337471744)
 * Caused by: Specified parameter is invalid
 *    at foo (stacktrace_example.c:7)
 *    at bar (stacktrace_example.c:16)
 *    at main (stacktrace_example.c:31)
 */
int main() {
    void *arg;

    arg = NULL;

    ei_init();

    if (!bar(arg)) {
        ei_stacktrace_push_msg("bar failed !");
    }

    if (ei_stacktrace_is_filled()) {
        ei_stacktrace_print();
    }

    ei_uninit();

    return EXIT_SUCCESS;
}
