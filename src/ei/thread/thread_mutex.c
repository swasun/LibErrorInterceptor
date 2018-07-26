/*******************************************************************************
 * Copyright (C) 2018 Charly Lamothe                                           *
 *                                                                             *
 * This file is part of LibErrorInterceptor.                                   *
 *                                                                             *
 *   Licensed under the Apache License, Version 2.0 (the "License");           *
 *   you may not use this file except in compliance with the License.          *
 *   You may obtain a copy of the License at                                   *
 *                                                                             *
 *   http://www.apache.org/licenses/LICENSE-2.0                                *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************/

#include <ei/thread/thread_mutex.h>
#include <ei/stacktrace/stacktrace.h>
#include <ei/logger/logger.h>
#include <ei/alloc.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <ei/error/error.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <string.h>

/*
 * For Windows :
 * http://preshing.com/20111124/always-use-a-lightweight-mutex/
 */
ei_thread_mutex *ei_thread_mutex_create() {
    ei_thread_mutex *m;

    m = NULL;

    ei_safe_alloc(m, ei_thread_mutex, 1);

#if defined(_WIN32) || defined(_WIN64)
        InitializeCriticalSection(&m->lock);
#else
        errno = 0;
        if (pthread_mutex_init(&m->lock, NULL) != 0) {
            ei_safe_free(m);
            fprintf(stderr, "[LIBEI] [ERROR] [MUTEX] [ei_thread_mutex_create()] pthread_mutex_init() failed with error message: %s\n", strerror(errno));
            return NULL;
        }
#endif

    return m;
}

bool ei_thread_mutex_destroy(ei_thread_mutex *m) {
    bool state;

    if (!m) {
        fprintf(stderr, "[LIBEI] [ERROR] [MUTEX] [ei_thread_mutex_lock()] Invalid parameter\n");
        return true;
    }

    state = true;

#if defined(_WIN32) || defined(_WIN64)
        DeleteCriticalSection(&m->lock);
#else
        errno = 0;
        if (pthread_mutex_destroy(&m->lock) != 0) {
            fprintf(stderr, "[LIBEI] [ERROR] [MUTEX] [ei_thread_mutex_destroy()] pthread_mutex_destroy() failed with error message: %s\n", strerror(errno));
            state = false;
        }
#endif

    ei_safe_free(m);

    return state;
}

bool ei_thread_mutex_lock(ei_thread_mutex *m) {
    if (!m) {
        fprintf(stderr, "[LIBEI] [ERROR] [MUTEX] [ei_thread_mutex_lock()] Invalid parameter\n");
        return false;
    }

#if defined(_WIN32) || defined(_WIN64)
        TryEnterCriticalSection(&m->lock);
#else
        errno = 0;
        if (pthread_mutex_lock(&m->lock) != 0) {
            fprintf(stderr, "[LIBEI] [ERROR] [MUTEX] [ei_thread_mutex_destroy()] pthread_mutex_destroy() failed with error message: %s\n", strerror(errno));
            return false;
        }
#endif

    return true;
}

bool ei_thread_mutex_unlock(ei_thread_mutex *m) {
    if (!m) {
        fprintf(stderr, "[LIBEI] [ERROR] [MUTEX] [ei_thread_mutex_unlock()] Invalid parameter\n");
        return false;
    }

#if defined(_WIN32) || defined(_WIN64)
        LeaveCriticalSection(&m->lock);
#else
        errno = 0;
        if (pthread_mutex_unlock(&m->lock) != 0) {
            fprintf(stderr, "[LIBEI] [ERROR] [MUTEX] [ei_thread_mutex_unlock()] pthread_mutex_unlock() failed with error message: %s\n", strerror(errno));
            return false;
        }
#endif

    return true;
}
