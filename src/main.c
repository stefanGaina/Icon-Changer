/******************************************************************************************************
 * @file main.c                                                                                       *
 * @date:      @author:                   Reason for change:                                          *
 * 27.06.2023  Gaina Stefan               Initial version.                                            *
 * @details This file provides an entry point for the tool and also the algorithm that does the       *
 * change of the icon.                                                                                *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <Windows.h>
#include <inttypes.h>
#include <stdio.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The major version of the tool.
*/
#define VERSION_MAJOR 1

/**
 * @brief The minor version of the tool.
*/
#define VERSION_MINOR 0

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

/**
 * @brief https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/access-waccess?view=msvc-160
*/
extern int access(const char* path, int mode);

/******************************************************************************************************
 * LOCAL FUNCTIONS                                                                                    *
 *****************************************************************************************************/

/**
 * @brief Changes the icon of an executable.
 * @param[in] icon_path: The path to the icon that will be changed.
 * @param[in] executable_path: The path to the executable which icon will be changed.
 * @return void
*/
static void change_executable_icon(const char* icon_path, const char* executable_path);

/******************************************************************************************************
 * ENTRY POINT                                                                                        *
 *****************************************************************************************************/

int main(int argc, char* argv[])
{
	if (2L == argc && 0L == strcmp("--version", argv[1]))
	{
		(void)fprintf(stdout, "Icon-Changer version %" PRId32 ".%" PRId32 "!\n", VERSION_MAJOR, VERSION_MINOR);
		return EXIT_SUCCESS;
	}

	if (3L > argc)
	{
		(void)fprintf(stdout, "Usage: <icon-changer.exe> <path_to_icon> <path_to_exe>\n");
		return EXIT_FAILURE;
	}

	if (0L > access(argv[1], 0L))
	{
		(void)fprintf(stdout, "Icon not found!\n");
		return EXIT_FAILURE;
	}

	if (0L > access(argv[2], 0L))
	{
		(void)fprintf(stdout, "Executable not found!\n");
		return EXIT_FAILURE;
	}

	change_executable_icon(argv[1], argv[2]);

	return EXIT_SUCCESS;
}

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

static void change_executable_icon(const char* icon_path, const char* executable_path)
{
	void*   icon_file         = CreateFileA(icon_path, 0x80000000L, 0L, NULL, 3L, 0L, NULL);
	void*   icon_info         = NULL;
	size_t  icon_info_address = 0ULL;
	int32_t image_offset      = 0L;
	int32_t image_size        = 0L;
	void*   icon_read_buffer  = NULL;
	void*   update_resource   = NULL;

	/* read 1st 22 bytes from ico file: https://en.wikipedia.org/wiki/ICO_(file_format) */
	icon_info = malloc(22ULL);
	if (NULL == icon_info)
	{
		(void)fprintf(stdout, "Out of memory! Couldn't allocate %" PRIu64 "bytes\n", 22ULL);
		return;
	}
	icon_info_address = (size_t)icon_info;

	(void)ReadFile(icon_file, icon_info, 22L, NULL, NULL);

	/* Check if 1st 2 WORDs of .ico file are valid */
	if (0 != *(int16_t*)icon_info_address || 1 != *(int16_t*)(icon_info_address + 2))
	{
		(void)fprintf(stdout, "Icon is not a valid .ico file!\n");
		free(icon_info);
		(void)CloseHandle(icon_file);

		return;
	}

	image_offset = *(int32_t*)(icon_info_address + 18ULL);
	image_size   = *(int32_t*)(icon_info_address + 14ULL);

	icon_read_buffer = malloc((size_t)image_size);
	if (NULL == icon_read_buffer)
	{
		(void)fprintf(stdout, "Out of memory! Couldn't allocate %" PRId32 "bytes\n", image_size);
		free(icon_info);
		(void)CloseHandle(icon_file);

		return;
	}

	(void)SetFilePointer(icon_file, image_offset, NULL, 0L);
	(void)ReadFile(icon_file, icon_read_buffer, image_size, NULL, NULL);
	(void)CloseHandle(icon_file);

	*(int16_t*)(icon_info_address + 4ULL)  = 1;
	*(int16_t*)(icon_info_address + 18ULL) = 1;

	update_resource = BeginUpdateResourceA(executable_path, 0L);
	(void)UpdateResourceA(update_resource, (char*)3 , (char*)1, 0L, icon_read_buffer, image_size);
	(void)UpdateResourceA(update_resource, (char*)14, (char*)1, 0L, icon_info, 20L);
	(void)EndUpdateResourceA(update_resource, FALSE);

	free(icon_info);
	free(icon_read_buffer);
}
