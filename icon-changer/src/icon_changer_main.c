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
 * @file icon_changer_main.c                                                                          *
 * @date:      @author:                   Reason for change:                                          *
 * 27.06.2023  Gaina Stefan               Initial version.                                            *
 * 05.08.2023  Gaina Stefan               Made parameterized pointers const.                          *
 * 14.08.2023  Gaina Stefan               Moved the change icon function.                             *
 * 16.09.2023  Gaina Stefan               Renamed file name.                                          *
 * 30.12.2023  Gaina Stefan               Added copyright.                                            *
 * @details This file provides an entry point for the tool and also the algorithm that does the       *
 * change of the icon.                                                                                *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "icon_changer.h"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The major version of the tool.
*/
static const uint8_t VERSION_MAJOR = 1U;

/**
 * @brief The minor version of the tool.
*/
static const uint8_t VERSION_MINOR = 0U;

/**
 * @brief The patch version of the tool.
*/
static const uint8_t VERSION_PATCH = 0U;

/******************************************************************************************************
 * ENTRY POINT                                                                                        *
 *****************************************************************************************************/

int main(int argc, char* argv[])
{
	if (2 == argc && (0 == strcmp("--version", argv[1]) || 0L == strcmp("-v", argv[1])))
	{
		(void)fprintf(stdout, "Icon-Changer version %" PRIu8 ".%" PRIu8 " .%" PRIu8 "!\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
		return EXIT_SUCCESS;
	}

	if (3 > argc)
	{
		(void)fprintf(stdout, "Usage: <%s> <path_to_icon> <path_to_exe>\n", argv[0]);
		return EXIT_FAILURE;
	}

	return true == change_executable_icon(argv[1], argv[2]) ? EXIT_SUCCESS : EXIT_FAILURE;
}
