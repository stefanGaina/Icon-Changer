/******************************************************************************************************
 * @file icon_changer.c                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 14.08.2023  Gaina Stefan               Initial version.                                            *
 * 16.09.2023  Gaina Stefan               Added checks for files existence.                           *
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
	void* const icon_file        = CreateFileA(icon_path, 0x80000000L, 0L, NULL, 3L, 0L, NULL);
	void*       icon_info        = NULL;
	int32_t     image_offset     = 0L;
	int32_t     image_size       = 0L;
	void*       icon_read_buffer = NULL;
	void*       update_resource  = NULL;

	if (-1L == access(icon_path, 0L))
	{
		(void)fprintf(stdout, "Icon not found!\n");
		return false;
	}

	if (-1L == access(executable_path, 0L))
	{
		(void)fprintf(stdout, "Executable not found!\n");
		return false;
	}

	/* read 1st 22 bytes from ico file: https://en.wikipedia.org/wiki/ICO_(file_format) */
	icon_info = malloc(22ULL);
	if (NULL == icon_info)
	{
		(void)fprintf(stdout, "Couldn't allocate memory for icon information! (bytes: %" PRIu64 ")\n", 22ULL);
		return false;
	}

	(void)ReadFile(icon_file, icon_info, 22L, NULL, NULL);

	/* Check if first 2 WORDs of .ico file are valid */
	if (0 != *(int16_t*)icon_info || 1 != *(int16_t*)((int8_t*)icon_info + 2ULL))
	{
		(void)fprintf(stdout, "Icon is not a valid .ico file!\n");
		free(icon_info);
		(void)CloseHandle(icon_file);

		return false;
	}

	image_offset = *(int32_t*)((int8_t*)icon_info + 18ULL);
	image_size   = *(int32_t*)((int8_t*)icon_info + 14ULL);

	icon_read_buffer = malloc((size_t)image_size);
	if (NULL == icon_read_buffer)
	{
		(void)fprintf(stdout, "Couldn't allocate memory for icon buffer! (bytes: %" PRId32 ")\n", image_size);
		free(icon_info);
		(void)CloseHandle(icon_file);

		return false;
	}

	(void)SetFilePointer(icon_file, image_offset, NULL, 0L);
	(void)ReadFile(icon_file, icon_read_buffer, image_size, NULL, NULL);
	(void)CloseHandle(icon_file);

	*(int16_t*)((int8_t*)icon_info + 4ULL)  = 1;
	*(int16_t*)((int8_t*)icon_info + 18ULL) = 1;

	update_resource = BeginUpdateResourceA(executable_path, 0L);
	(void)UpdateResourceA(update_resource, (char*)3 , (char*)1, 0L, icon_read_buffer, image_size);
	(void)UpdateResourceA(update_resource, (char*)14, (char*)1, 0L, icon_info, 20L);
	(void)EndUpdateResourceA(update_resource, FALSE);

	free(icon_info);
	free(icon_read_buffer);

	return true;
}
