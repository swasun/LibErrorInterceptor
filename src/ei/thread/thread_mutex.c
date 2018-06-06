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

#include <ei/thread/thread_mutex.h>
#include <ei/check_parameter.h>
#include <ei/stacktrace/stacktrace.h>
#include <ei/logger/logger.h>
#include <ei/alloc.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <unknownecho/errorHandling/error.h>
#endif

#include <errno.h>

/*
 * For Windows :
 * http://preshing.com/20111124/always-use-a-lightweight-mutex/
 */
ei_thread_mutex *ei_thread_mutex_create() {
    ei_thread_mutex *m;
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    ei_safe_alloc(m, ei_thread_mutex, 1);

#if defined(_WIN32) || defined(_WIN64)
        InitializeCriticalSection(&m->lock);
        /*if (!(m->lock = CreateMutex(NULL, FALSE, NULL))) {
            ei_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ei_safe_free(error_buffer);
            ei_safe_free(m);
            return NULL;
        }*/
#else
        if (pthread_mutex_init(&m->lock, NULL) != 0) {
            ei_safe_free(m);
            ei_stacktrace_push_errno();
            return NULL;
        }
#endif

    return m;
}

bool ei_thread_mutex_destroy(ei_thread_mutex *m) {
    bool state;
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    if (!m) {
        return true;
    }

    state = true;

#if defined(_WIN32) || defined(_WIN64)
        DeleteCriticalSection(&m->lock);
        /*if (!CloseHandle(m->lock)) {
            ei_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ei_safe_free(error_buffer);
            state = false;
        }*/
#else
        if (pthread_mutex_destroy(&m->lock) != 0) {
            ei_stacktrace_push_errno();
            state = false;
        }
#endif

    ei_safe_free(m);

    return state;
}

bool ei_thread_mutex_lock(ei_thread_mutex *m) {
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    ei_check_parameter_or_return(m)

#if defined(_WIN32) || defined(_WIN64)
        TryEnterCriticalSection(&m->lock);
        /*if (WaitForSingleObject(m->lock, INFINITE) == WAIT_FAILED) {
            ei_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ei_safe_free(error_buffer);
            return false;
        }*/
#else
        if (pthread_mutex_lock(&m->lock) != 0) {
            ei_stacktrace_push_errno();
            return false;
        }
#endif

    return true;
}

bool ei_thread_mutex_unlock(ei_thread_mutex *m) {
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    ei_check_parameter_or_return(m);

#if defined(_WIN32) || defined(_WIN64)
        LeaveCriticalSection(&m->lock);
        /*if (!ReleaseMutex(m->lock)) {
            ei_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ei_safe_free(error_buffer);
            return false;
        }*/
#else
        if (pthread_mutex_unlock(&m->lock) != 0) {
            ei_stacktrace_push_errno();
            return false;
        }
#endif

    return true;
}
