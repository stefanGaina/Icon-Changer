/******************************************************************************************************
 * @file main.c                                                                                       *
 * @date:      @author:                   Reason for change:                                          *
 * 27.06.2023  Gaina Stefan               Initial version.                                            *
 * 05.08.2023  Gaina Stefan               Made parameterized pointers const.                          *
 * 14.08.2023  Gaina Stefan               Moved the change icon function.                             *
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
#define VERSION_MAJOR (uint8_t)1U

/**
 * @brief The minor version of the tool.
*/
#define VERSION_MINOR (uint8_t)0U

/**
 * @brief The patch version of the tool.
*/
#define VERSION_PATCH (uint8_t)2U

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

/**
 * @brief https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/access-waccess?view=msvc-160
*/
extern int access(const char* path, int mode);

/******************************************************************************************************
 * ENTRY POINT                                                                                        *
 *****************************************************************************************************/

int main(int argc, char* argv[])
{
	if (2L == argc && 0L == strcmp("--version", argv[1]))
	{
		(void)fprintf(stdout, "Icon-Changer version %" PRIu8 ".%" PRIu8 " .%" PRIu8 "!\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
		return EXIT_SUCCESS;
	}

	if (3L > argc)
	{
		(void)fprintf(stdout, "Usage: <%s.exe> <path_to_icon> <path_to_exe>\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (-1L == access(argv[1], 0L))
	{
		(void)fprintf(stdout, "Icon not found!\n");
		return EXIT_FAILURE;
	}

	if (-1L == access(argv[2], 0L))
	{
		(void)fprintf(stdout, "Executable not found!\n");
		return EXIT_FAILURE;
	}

	return true == change_executable_icon(argv[1], argv[2]) ? EXIT_SUCCESS : EXIT_FAILURE;
}
