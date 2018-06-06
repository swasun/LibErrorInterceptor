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
 *  @file      check_parameter.h
 *  @brief     Provides macro to record ERRORINTERCEPTOR_INVALID_PARAMETER error code
 *             and return if specified parameter is null.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef ERRORINTERCEPTOR_CHECK_PARAMETER_H
#define ERRORINTERCEPTOR_CHECK_PARAMETER_H

#include <ei/stacktrace/stacktrace.h>
#include <ei/error/error.h>

#define ei_unused(x) (void)(x);

#define ei_check_parameter(p) \
    if (!(p)) { \
        ei_stacktrace_push_code(ERRORINTERCEPTOR_INVALID_PARAMETER) \
        return; \
    } \

#define ei_check_parameter_or_return(p) \
    if (!(p)) { \
        ei_stacktrace_push_code(ERRORINTERCEPTOR_INVALID_PARAMETER) \
        return 0; \
    } \

#define ei_check_parameter_or_goto(p, label) \
    if (!(p)) { \
        ei_stacktrace_push_code(ERRORINTERCEPTOR_INVALID_PARAMETER) \
        goto label; \
    } \

#endif /* CHECK_PARAMETER_H */
