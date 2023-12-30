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
 * @file icon_changer.c                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 14.08.2023  Gaina Stefan               Initial version.                                            *
 * 16.09.2023  Gaina Stefan               Added checks for files existence.                           *
 * 30.12.2023  Gaina Stefan               Added copyright.                                            *
 * @details This file implements the interface defined in icon_changer.h.                             *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <stdio.h>
#include <inttypes.h>
#include <windows.h>

#include "icon_changer.h"

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

/**
 * @brief https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/access-waccess?view=msvc-160
*/
extern int access(const char* path, int mode);

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

bool change_executable_icon(const char* const icon_path, const char* const executable_path)
{
	void* const icon_file        = CreateFileA(icon_path, 0x80000000, 0, NULL, 3, 0, NULL);
	void*       icon_info        = NULL;
	int32_t     image_offset     = 0;
	int32_t     image_size       = 0;
	void*       icon_read_buffer = NULL;
	void*       update_resource  = NULL;

	if (-1 == access(icon_path, 0))
	{
		(void)fprintf(stdout, "Icon not found!\n");
		return false;
	}

	if (-1 == access(executable_path, 0))
	{
		(void)fprintf(stdout, "Executable not found!\n");
		return false;
	}

	/* read 1st 22 bytes from ico file: https://en.wikipedia.org/wiki/ICO_(file_format) */
	icon_info = malloc(22UL);
	if (NULL == icon_info)
	{
		(void)fprintf(stdout, "Couldn't allocate memory for icon information! (bytes: %" PRIu64 ")\n", 22UL);
		return false;
	}

	(void)ReadFile(icon_file, icon_info, 22, NULL, NULL);

	/* Check if first 2 WORDs of .ico file are valid */
	if (0 != *(int16_t*)icon_info || 1 != *(int16_t*)((int8_t*)icon_info + 2))
	{
		(void)fprintf(stdout, "Icon is not a valid .ico file!\n");
		free(icon_info);
		(void)CloseHandle(icon_file);

		return false;
	}

	image_offset = *(int32_t*)((int8_t*)icon_info + 18);
	image_size   = *(int32_t*)((int8_t*)icon_info + 14);

	icon_read_buffer = malloc((size_t)image_size);
	if (NULL == icon_read_buffer)
	{
		(void)fprintf(stdout, "Couldn't allocate memory for icon buffer! (bytes: %" PRId32 ")\n", image_size);
		free(icon_info);
		(void)CloseHandle(icon_file);

		return false;
	}

	(void)SetFilePointer(icon_file, image_offset, NULL, 0);
	(void)ReadFile(icon_file, icon_read_buffer, image_size, NULL, NULL);
	(void)CloseHandle(icon_file);

	*(int16_t*)((int8_t*)icon_info + 4)  = 1;
	*(int16_t*)((int8_t*)icon_info + 18) = 1;

	update_resource = BeginUpdateResourceA(executable_path, 0L);
	(void)UpdateResourceA(update_resource, (char*)3 , (char*)1, 0, icon_read_buffer, image_size);
	(void)UpdateResourceA(update_resource, (char*)14, (char*)1, 0, icon_info, 20);
	(void)EndUpdateResourceA(update_resource, FALSE);

	free(icon_info);
	free(icon_read_buffer);

	return true;
}
