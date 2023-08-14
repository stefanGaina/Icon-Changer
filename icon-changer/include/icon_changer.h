/******************************************************************************************************
 * @file icon_changer.h                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 14.08.2023  Gaina Stefan               Initial version.                                            *
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
