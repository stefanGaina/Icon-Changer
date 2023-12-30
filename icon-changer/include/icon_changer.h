/******************************************************************************************************
 * Icon-Changer Copyright (C) 2024                                                                    *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file icon_changer.h                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 14.08.2023  Gaina Stefan               Initial version.                                            *
 * 30.12.2023  Gaina Stefan               Added copyright.                                            *
 * @details This file defines the function prototype of changing executable icon.                     *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef ICON_CHANGER_H_
#define ICON_CHANGER_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <stdbool.h>

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

/**
 * @brief Changes the icon of an executable.
 * @param[in] icon_path: The path to the icon that will be changed.
 * @param[in] executable_path: The path to the executable which icon will be changed.
 * @return true - icon changed successfully | false - otherwise.
*/
extern bool change_executable_icon(const char* icon_path, const char* executable_path);

#endif /*< ICON_CHANGER_H_ */
