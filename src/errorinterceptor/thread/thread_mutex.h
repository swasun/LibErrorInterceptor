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
 *  @file      thread_mutex.h
 *  @brief     Portable structure of thread mutex.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_THREAD_MUTEX_H
#define ERRORINTERCEPTOR_THREAD_MUTEX_H

#include <errorinterceptor/bool.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <pthread.h>
#endif

typedef struct {
#if defined(_WIN32) || defined(_WIN64)
        //HANDLE lock;
        CRITICAL_SECTION lock;
#else
        pthread_mutex_t lock;
#endif
} ei_thread_mutex;

ei_thread_mutex *ei_thread_mutex_create();

/**
 * @todo In UNIX impl, detect EBUSY and try to destroy the mutex with a timeout.
 */
bool ei_thread_mutex_destroy(ei_thread_mutex *m);

bool ei_thread_mutex_lock(ei_thread_mutex *m);

bool ei_thread_mutex_unlock(ei_thread_mutex *m);

#endif
