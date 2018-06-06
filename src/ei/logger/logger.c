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

/*
 * Inspired by log.c of rxi on Github : https://github.com/rxi/log.c
 *
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#include <ei/logger/logger.h>
#include <ei/alloc.h>
#include <ei/string/string_utility.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEVEL_NAME_MAX_SIZE  7

#if defined(__unix__)

#define ERRORINTERCEPTOR_SKY_BLei_COLOR                   "\x1b[94m"
#define ERRORINTERCEPTOR_TURQUOISE_BLei_COLOR             "\x1b[36m"
#define ERRORINTERCEPTOR_GREEN_COLOR                      "\x1b[32m"
#define ERRORINTERCEPTOR_YELLOW_COLOR                     "\x1b[33m"
#define ERRORINTERCEPTOR_RED_COLOR                        "\x1b[31m"
#define ERRORINTERCEPTOR_PURPLE_COLOR                     "\x1b[35m"
#define ERRORINTERCEPTOR_GRAY_COLOR                       "\x1b[90m"
#define ERRORINTERCEPTOR_WHITE_COLOR                      "\x1b[0m"

#elif defined(_WIN32) || defined(_WIN64)

#define ERRORINTERCEPTOR_SKY_BLei_COLOR                   ""
#define ERRORINTERCEPTOR_TURQUOISE_BLei_COLOR             ""
#define ERRORINTERCEPTOR_GREEN_COLOR                      ""
#define ERRORINTERCEPTOR_YELLOW_COLOR                     ""
#define ERRORINTERCEPTOR_RED_COLOR                        ""
#define ERRORINTERCEPTOR_PURPLE_COLOR                     ""
#define ERRORINTERCEPTOR_GRAY_COLOR                       ""
#define ERRORINTERCEPTOR_WHITE_COLOR                      ""

#endif

static const char *level_names[] = {
    "TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"
};

ei_logger *ei_logger_create() {
    ei_logger *log;

    ei_safe_alloc(log, ei_logger, 1);
    log->print_level = 0;
    log->file_level = 0;
    log->fp = NULL;
    log->mutex = ei_thread_mutex_create();
    log->colored = true;
    log->details = true;
    log->padding = false;
    log->message_color_as_level_color = false;

    ei_safe_alloc(log->level_colors, char *, 6);
    log->level_colors[ERRORINTERCEPTOR_LOG_TRACE] = ei_string_create_from(ERRORINTERCEPTOR_SKY_BLei_COLOR);
    log->level_colors[ERRORINTERCEPTOR_LOG_DEBUG] = ei_string_create_from(ERRORINTERCEPTOR_TURQUOISE_BLei_COLOR);
    log->level_colors[ERRORINTERCEPTOR_LOG_INFO] = ei_string_create_from(ERRORINTERCEPTOR_GREEN_COLOR);
    log->level_colors[ERRORINTERCEPTOR_LOG_WARNING] = ei_string_create_from(ERRORINTERCEPTOR_YELLOW_COLOR);
    log->level_colors[ERRORINTERCEPTOR_LOG_ERROR] = ei_string_create_from(ERRORINTERCEPTOR_RED_COLOR);
    log->level_colors[ERRORINTERCEPTOR_LOG_FATAL] = ei_string_create_from(ERRORINTERCEPTOR_PURPLE_COLOR);

    log->message_color = ei_string_create_from(ERRORINTERCEPTOR_WHITE_COLOR);

    return log;
}

void ei_logger_destroy(ei_logger *log) {
    if (log) {
        ei_thread_mutex_destroy(log->mutex);
        ei_safe_free(log->level_colors[ERRORINTERCEPTOR_LOG_TRACE]);
        ei_safe_free(log->level_colors[ERRORINTERCEPTOR_LOG_DEBUG]);
        ei_safe_free(log->level_colors[ERRORINTERCEPTOR_LOG_INFO]);
        ei_safe_free(log->level_colors[ERRORINTERCEPTOR_LOG_WARNING]);
        ei_safe_free(log->level_colors[ERRORINTERCEPTOR_LOG_ERROR]);
        ei_safe_free(log->level_colors[ERRORINTERCEPTOR_LOG_FATAL]);
        ei_safe_free(log->level_colors);
        ei_safe_free(log->message_color);
        ei_safe_free(log);
    }
}

void ei_logger_set_fp(ei_logger *log, FILE *fp) {
    log->fp = fp;
}

void ei_logger_set_file_level(ei_logger *log, int level) {
    log->file_level = level;
}

void ei_logger_set_print_level(ei_logger *log, int level) {
    log->print_level = level;
}

int ei_logger_get_print_level(ei_logger *log) {
    return  log->print_level;
}

int ei_logger_get_file_level(ei_logger *log) {
    return  log->file_level;
}

void ei_logger_set_colored(ei_logger *log, bool enable) {
    log->colored = enable;
}

void ei_logger_set_details(ei_logger *log, bool enable) {
    log->details = enable;
}

void ei_logger_set_padding(ei_logger *log, bool enable) {
    log->padding = enable;
}

void ei_logger_set_message_color(ei_logger *log, const char *color) {
    ei_safe_free(log->message_color);
    log->message_color = ei_string_create_from(color);
}

void ei_logger_set_message_color_as_level_color(ei_logger *log, bool enable) {
    log->message_color_as_level_color = enable;
}

bool ei_logger_record(ei_logger *log, int level, const char *file, int line, const char *fmt, ...) {
    time_t rawtime;
    struct tm *timeinfo;
    va_list args;
    char *date_time;
    unsigned short int padding_size;
    char *message_color;

    if (!log) {
        return false;
    }

    /* Acquire lock */
    ei_thread_mutex_lock(log->mutex);

    /* Get current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    date_time = asctime(timeinfo);
    date_time[strlen(date_time) - 1] = '\0';

    if (log->padding) {
        padding_size = LEVEL_NAME_MAX_SIZE - strlen(level_names[level]);
    } else {
        padding_size = 0;
    }

    if (log->message_color_as_level_color) {
        message_color = log->level_colors[level];
    } else {
        message_color = log->message_color;
    }

    /* Log to stdout */
    if (level >= log->print_level) {
        if (log->colored) {
            if (log->details) {
                fprintf(stdout, "%s[%s] [%s:%d] ", log->level_colors[level], date_time, file, line);
            }

            fprintf(stdout, "%s[%s]%*s%s %s", log->level_colors[level], level_names[level], padding_size,
                "", ERRORINTERCEPTOR_WHITE_COLOR, message_color);
        } else {
            if (log->details) {
                fprintf(stdout, "[%s] [%s:%d] ", date_time, file, line);
            }

            fprintf(stdout, "[%s]%*s ", level_names[level], padding_size, "");
        }

        va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        va_end(args);
        if (log->colored) {
            fprintf(stdout, "%s", ERRORINTERCEPTOR_WHITE_COLOR);
        }
        fprintf(stdout, "\n");
    }

    /* Log to file */
    if (log->fp != NULL && level >= log->file_level) {
        if (log->details) {
            fprintf(log->fp, "[%s] [%s:%d] ", date_time, file, line);
        }

        fprintf(log->fp, "[%s]%*s ", level_names[level], padding_size, "");

        va_start(args, fmt);
        vfprintf(log->fp, fmt, args);
        va_end(args);

        fprintf(log->fp, "\n");
    }

    fflush(log->fp);

    /* Release lock */
    ei_thread_mutex_unlock(log->mutex);

    return true;
}

static void record_stacktrace(FILE *fp, ei_stacktrace *stacktrace) {
    ei_stacktrace_print_fd_this(stacktrace, fp);
}

bool ei_logger_record_stacktrace(ei_logger *log, ei_stacktrace *stacktrace, const char *message, const char *file, int line) {
    unsigned short int padding_size;
    time_t rawtime;
    struct tm *timeinfo;
    char *date_time, *message_color;

    if (!log) {
        ei_stacktrace_push_msg("Specified log ptr is null");
        return false;
    }

    /* Acquire lock */
    ei_thread_mutex_lock(log->mutex);

    /* Get current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    date_time = asctime(timeinfo);
    date_time[strlen(date_time) - 1] = '\0';

    if (log->padding) {
        padding_size = LEVEL_NAME_MAX_SIZE - strlen(level_names[ERRORINTERCEPTOR_LOG_WARNING]);
    } else {
        padding_size = 0;
    }

    /* Log to stdout */
    if (ERRORINTERCEPTOR_LOG_ERROR >= log->print_level) {
        if (log->message_color_as_level_color) {
            message_color = log->level_colors[ERRORINTERCEPTOR_LOG_ERROR];
        } else {
            message_color = log->message_color;
        }

        if (log->colored) {
            if (log->details) {
                fprintf(stdout, "%s[%s] [%s:%d] ", log->level_colors[ERRORINTERCEPTOR_LOG_ERROR], date_time, file, line);
            }

            fprintf(stdout, "%s[%s]%*s%s %s", log->level_colors[ERRORINTERCEPTOR_LOG_ERROR], level_names[ERRORINTERCEPTOR_LOG_ERROR], padding_size,
                "", ERRORINTERCEPTOR_WHITE_COLOR, message_color);
        } else {
            if (log->details) {
                fprintf(stdout, "[%s] [%s:%d] ", date_time, file, line);
            }

            fprintf(stdout, "[%s]%*s ", level_names[ERRORINTERCEPTOR_LOG_ERROR], padding_size, "");
        }

        fprintf(stdout, "%s", message);
        if (log->colored) {
            fprintf(stdout, "%s", ERRORINTERCEPTOR_WHITE_COLOR);
        }
        fprintf(stdout, "\n");
        record_stacktrace(stdout, stacktrace);
        fflush(stdout);
    }

    /* Log to file */
    if (log->fp != NULL && ERRORINTERCEPTOR_LOG_ERROR >= log->file_level) {
        if (log->details) {
            fprintf(log->fp, " [%s] [%s:%d] ", date_time, file, line);
        }

        fprintf(log->fp, "[%s]%*s %s\n", level_names[ERRORINTERCEPTOR_LOG_ERROR], padding_size, "", message);

        record_stacktrace(log->fp, stacktrace);
    }

    /* Release lock */
    ei_thread_mutex_unlock(log->mutex);

    return true;
}

FILE *ei_logger_get_fp(ei_logger *log) {
    return log->fp;
}
