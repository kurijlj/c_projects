/* ==========================================================================
 * spvalid.h - Validate user supplied system path.
 *
 *  Copyright (C) 2023 Ljubomir Kurij ljubomir_kurij@protonmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ========================================================================== */


/* ==========================================================================
 *
 * 2023-07-17 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * spvalid.h: created.
 *
 * ========================================================================== */

#ifndef SPVALID_H
#define SPVALID_H

/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* System specific headers */
#ifdef _WIN32
#include <strsafe.h>
#include <windows.h>
#else
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#endif

/* ==========================================================================
 * Macros section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * User Type: ps_flags_t
 * --------------------------------------------------------------------------
 *
 * Description:
 *     Path status flags type. It uses unsigned char as a base type. The six
 *     least significant bits are used for path status flags, as described:
 *          bit 0: empty file flag (file size is 0)
 *          bit 1: file flag (path is a file)
 *          bit 2: empty directory flag (directory is empty)
 *          bit 3: directory flag (path is a directory)
 *          bit 4: exists flag (path exists)
 *          bit 5: empty flag (path is empty string)
 *
 *      The two most significant bits are reserved for future use.
 *
 * Example:
 *     ps_flags_t path_status = 0;
 *
 * -------------------------------------------------------------------------- */
typedef unsigned char ps_flags_t;

/* Define path status flags common operations */
#define path_set_empty(path_status, empty_flag) \
    (path_status | (empty_flag << 5))
#define path_set_exist(path_status, exist_flag) \
    (path_status | (exist_flag << 4))
#define path_set_dir(path_status, dir_flag) \
    (path_status | (dir_flag << 3))
#define path_set_dir_empty(path_status, dir_empty_flag) \
    (path_status | (dir_empty_flag << 2))
#define path_set_file(path_status, file_flag) \
    (path_status | (file_flag << 1))
#define path_set_file_empty(path_status, file_empty_flag) \
    (path_status | file_empty_flag)
#define path_is_empty(path_status) \
    ((path_status & (1 << 5)) >> 5)
#define path_exists(path_status) \
    ((path_status & (1 << 4)) >> 4)
#define path_is_dir(path_status) \
    ((path_status & (1 << 3)) >> 3)
#define path_is_empty_dir(path_status) \
    ((path_status & (1 << 2)) >> 2)
#define path_is_file(path_status) \
    ((path_status & (1 << 1)) >> 1)
#define path_is_empty_file(path_status) \
    (path_status & 1)

/* ==========================================================================
 * Utility functions section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: void printBits(unsigned char c)
 * --------------------------------------------------------------------------
 *
 * Description:
 *      Print bits of a byte. Used for debugging purposes.
 *
 * Parameters:
 *      c: byte to print bits of.
 *
 * Returns:
 *      void
 *
 * Example:
 *      printBits(0x0F);
 *
 * Output:
 *      00001111
 *
 * ----------------------------------------------------------------------- -- */
void printBits(unsigned char c) {
    for (int i = 7; i >= 0; i--) {
        unsigned char mask = 1 << i;
        putchar((c & mask) ? '1' : '0');
    }
    printf("\n");
}

/* ==========================================================================
 * System path validation functions section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: ps_flags_t validate_path(const char * const path)
 * --------------------------------------------------------------------------
 *
 * Description:
 *     Validate user supplied system path.
 *
 * Parameters:
 *      path: user supplied system path.
 *
 * Returns:
 *      path_status: path status flags.
 *
 * Example:
 *      ps_flags_t path_status
 *          = validate_path("C:\\Windows\\System32\\drivers");
 *
 * Output:
 *      path_status = 00000000
 *
 * ----------------------------------------------------------------------- -- */
ps_flags_t validate_path(const char * const path) {
    /* Initialize path status flags */
    ps_flags_t path_status = 0;

    /* Check if path is empty string */
    if (path[0] == '\0') {
        path_status = path_set_empty(path_status, 1);

    } else {
        /* Check if path exists */
        #ifndef _WIN32
        /* Windows specific code */
        DWORD dwAttrib = GetFileAttributes(path);

        if (INVALID_FILE_ATTRIBUTES != dwAttrib) {
            path_status = path_set_exist(path_status, 1);

            /* Check if path is a directory */
            if (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) {
                /* Path is a directory */
                path_status = path_set_dir(path_status, 1);

                /* Check if directory is empty */
                WIN32_FIND_DATA ffd;
                HANDLE hFind = INVALID_HANDLE_VALUE;

                /* Create the search pattern */
                char szSrchPat[FILENAME_MAX];
                snprintf(szSrchPat, FILENAME_MAX, "%s\\*.*", path);

                /* Find the first file in the directory */
                hFind = FindFirstFileA(szSrchPat, &ffd);
                if (INVALID_HANDLE_VALUE == hFind) {
                    /* We an error that we don't handle. Print the error message
                     * and bail out.
                     */
                    ReportWin32SysError(TEXT(kAppNAme), TEXT("FindFirstFileA"));

                    exit(EXIT_FAILURE);

                }

                /* Loop over all the files in the directory */
                do {
                    /* Skip the current and parent directory */
                    if (strcmp(ffd.cFileName, ".") == 0
                        || strcmp(ffd.cFileName, "..") == 0) {
                        continue;
                    }

                    /* Directory is not empty */
                    path_status = path_set_dir_empty(path_status, 0);

                    /* Stop searching */
                    break;

                } while (FindNextFileA(hFind, &ffd) != 0);

                /* Close the search handle */
                FindClose(hFind);

            /* Check if path is a file */
            } else {
                /* Path is a file */
                path_status = path_set_file(path_status, 1);

                /* Check if file is empty */
                HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL,
                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

                if (hFile != INVALID_HANDLE_VALUE) {
                    /* File exists */
                    path_status = path_set_file_empty(path_status, 1);

                    /* Get file size */
                    LARGE_INTEGER liFileSize;

                    if (GetFileSizeEx(hFile, &liFileSize)) {
                        if (liFileSize.QuadPart == 0) {
                            /* File is empty */
                            path_status = path_set_file_empty(path_status, 1);

                        } else {
                            /* File is not empty */
                            path_status = path_set_file_empty(path_status, 0);
                        }

                    } else {
                        /* Could not get file size */
                        path_status = path_set_file_empty(path_status, 0);
                    }

                    CloseHandle(hFile);

                } else {
                    /* File does not exist */
                    path_status = path_set_file_empty(path_status, 1);
                }
            }

        } /* End of path exists branch */

        /* Assume path does not exist */

        #else
        /* POSIX specific code */
        #endif  /* End of _WIN32 */

    }  /* End of path != '\0' branch */

    return path_status;



#endif  /* SPVALID_H */