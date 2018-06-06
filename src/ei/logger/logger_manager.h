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
 *  @file      logger_manager.h
 *  @brief     Logger manager return the current (thread-local) logger.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 *  @see       logger.h
 *  @see       logger_struct.h
 */

#ifndef ERRORINTERCEPTOR_LOGGER_MANAGER_H
#define ERRORINTERCEPTOR_LOGGER_MANAGER_H

#include <ei/bool.h>
#include <ei/logger/logger_struct.h>
#include <ei/logger/logger.h>

bool ei_logger_manager_init();

void ei_logger_manager_uninit();

ei_logger *ei_logger_manager_get_logger();

#endif
