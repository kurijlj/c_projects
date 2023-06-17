/* ==========================================================================
 * <one line to give the program's name and a brief idea of what it does.>
 *
 *  Copyright (C) <yyyy> <Author Name> <author@mail.com>
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
 * <Put documentation here>
 *
 * <yyyy>-<mm>-<dd> <Author Name> <author@mail.com>
 *
 * * <programfilename>.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 *
 * References (this section should be deleted in the release version)
 *
 * * For coding style visit GNU Coding Standards page at
 *   <https://www.gnu.org/prep/standards/html_node/index.html>.
 *
 * * For command line arguments parsing using argparse consult documentation
 *   and examples at <https://github.com/cofyc/argparse>.
 *
 * ========================================================================== */


/* ==========================================================================
 * Define section
 * ========================================================================== */

/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */
#include <argparse.h>

/* System specific headers */
#ifdef _WIN32
#include <strsafe.h>
#include <windows.h>
#else
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#endif

/* Find a missing semi-colon in the following code */
/* ==========================================================================
 * Global variables section
 * ========================================================================== */

static const char *const kAppName = "system_path_validators";
static const char *const kDescription = "\n\
Main framework module for developing apps using \"GNU Scientific Library\".\n\n\
Mandatory arguments to long options are mandatory for short options too.";
static const char *const kEpilogue = "\n\
Report bugs to <author@email.com>.";
static const char *const kUsages[] = {
    "app_name [OPTION]...",
    "app_name ...",
    NULL,
};


/* ==========================================================================
 * Utility function declarations
 * ========================================================================== */

void short_usage(
        struct argparse *self,
        const struct argparse_option *option
        );
void version_info(
        struct argparse *self,
        const struct argparse_option *option
        );
void ReportWin32SystemError(LPSTR lpszAppName, LPTSTR lpszFunction) ;


/* ==========================================================================
 * Main module
 * ========================================================================== */

int main(int argc, const char **argv) {

    int usage = 0;
    int version = 0;
    char * const path = NULL;

    struct argparse_option options[] = {
        OPT_GROUP("general options"),
        OPT_HELP(),
        OPT_BOOLEAN('\0', "usage", &usage, "give a short usage message",
                &short_usage, 0, 0),
        OPT_BOOLEAN('V', "version", &version, "print program version", 
                &version_info, 0, 0),
        OPT_GROUP("system path options"),
        OPT_STRING('p', "path", &path, "path to be validated", NULL, 0, 0),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, kUsages, 0);
    argparse_describe(&argparse, kDescription, kEpilogue);
    argc = argparse_parse(&argparse, argc, argv);

    if (usage != 0 || version != 0) {
        exit(EXIT_SUCCESS);

    }

    if (argc != 0) {
        /* User supplied an option that is not defined */
        printf("%s: Unknown command line option: %s\n", kAppName, argv[0]);
        short_usage(&argparse, NULL);

        exit(EXIT_FAILURE);

    } else {
        /* Execute main module */
        printf("%s: Main module running ...\n", kAppName);

        if(path != NULL) {
            printf("%s: Path: %s\n", kAppName, path);

            /* Check if user supplied an empty string */
            if ('\0' == *path)
            {
                printf("%s: Path is empty.\n", kAppName);

            } else {

                DWORD dwAttrib = GetFileAttributes(path);

                #ifdef _WIN32
                /* Execute Windows specific code */
                if (INVALID_FILE_ATTRIBUTES == dwAttrib
                        && GetLastError() == ERROR_FILE_NOT_FOUND) {
                    /* Check if path exists */
                    printf("%s: Path does not exist.\n", kAppName);

                } else if(FILE_ATTRIBUTE_DIRECTORY & dwAttrib) {
                    /* Check if path is a directory */
                    printf("%s: Path is a directory.\n", kAppName);

                    /* Given path is a directory. Let's check if it is empty */
                    WIN32_FIND_DATAA findData;
                    HANDLE hFind;
                    bool is_empty = true;

                    /* Create a search pattern */
                    char search_pattern[FILENAME_MAX];
                    snprintf(search_pattern, FILENAME_MAX, "%s\\*.*", path);

                    /* Search for the first file in the directory */
                    hFind = FindFirstFileA(search_pattern, &findData);
                    if (INVALID_HANDLE_VALUE == hFind) {
                        /* We have an error. Print the error message and exit */
                        ReportWin32SystemError(TEXT(kAppName),
                                TEXT("FindFirstFileA"));

                        exit(EXIT_FAILURE);

                    }

                    do {
                        /* Ignore "." and ".." directories */
                        strncmp(findData.cFileName, ".", 1);
                        if (strncmp(findData.cFileName, ".",
                                    FILENAME_MAX) != 0
                                && strncmp(findData.cFileName, "..",
                                    FILENAME_MAX) != 0) {
                            /* Directory is not empty */
                            is_empty = false;
                            FindClose(hFind);

                            /* We found some content in the directory.
                               Exit the loop
                             */
                            break;

                        }

                    } while (FindNextFileA(hFind, &findData) != 0);

                    /* Close find handle */
                    FindClose(hFind);

                    /* Print message for the user */
                    if (is_empty) {
                        printf("%s: Directory is empty.\n", kAppName);

                    } else {
                        printf("%s: Directory is not empty.\n", kAppName);

                    }

                } else if(FILE_ATTRIBUTE_NORMAL & dwAttrib
                    || FILE_ATTRIBUTE_ARCHIVE & dwAttrib) {
                    /* Check if path is a file */
                    printf("%s: Path is a file.\n", kAppName);

                    /* Given path is a file. Let's check if it is empty */
                    HANDLE hFile;
                    bool is_empty = true;

                    /* Open the file */
                    hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                    if (INVALID_HANDLE_VALUE == hFile) {
                        /* We have an error. Print the error message and exit */
                        ReportWin32SystemError(TEXT(kAppName),
                                TEXT("CreateFileA"));

                        exit(EXIT_FAILURE);

                    }

                    /* Get the file size */
                    DWORD fileSize = GetFileSize(hFile, NULL);

                    /* Check if file size is zero */
                    if (0 != fileSize) {
                        /* File is not empty */
                        is_empty = false;

                    }

                    /* Close file handle */
                    CloseHandle(hFile);

                    /* Print message for the user */
                    if (is_empty) {
                        printf("%s: File is empty.\n", kAppName);

                    } else {
                        printf("%s: File is not empty.\n", kAppName);

                    }

                }

                #else
                /* Execute POSIX specific code */
                struct stat st;
                if(stat(path, &st) == 0) {
                    /* Check if path exists */
                    printf("%s: Path exists.\n", kAppName);

                } else if(S_ISDIR(st.st_mode)) {
                    /* Check if path is a directory */
                    printf("%s: Path is a directory.\n", kAppName);

                    /* Given path is a directory. Let's check if it is empty */
                    DIR *directory;
                    struct dirent *entry;
                    bool is_empty = true;

                    /* Resete the error status value */
                    errno = 0;

                    /* Open the directory */
                    directory = opendir(path);
                    if (directory == NULL) {
                        /* We have an error. Print the error message and exit */
                        if(errno != 0) {
                            perror("opendir");
                        } else {
                            printf("%s: opendir() failed for unknown reason.\n",
                                    kAppName);
                        }

                        exit(EXIT_FAILURE);

                    }

                    /* Read directory entries */
                    while ((entry = readdir(directory)) != NULL) {
                        /* Ignore "." and ".." entries */
                        if (strncmp(entry->d_name, ".", FILENAME_MAX) != 0
                                && strncmp(entry->d_name, "..",
                                    FILENAME_MAX) != 0) {
                            /* Directory is not empty */
                            is_empty = false;
                            closedir(directory);

                            /* We found some content in the directory.
                               Exit the loop
                             */
                            break;

                        }

                    }
                    closedir(directory);

                    if (is_empty) {
                        printf("%s: Directory is empty.\n", kAppName);

                    } else {
                        printf("%s: Directory is not empty.\n", kAppName);

                    }

                } else if(S_ISREG(st.st_mode)) {
                    /* Check if path is a file */
                    printf("%s: Path is a file.\n", kAppName);

                    /* Given path is a file. Let's check if it is empty */
                    FILE *file;
                    bool is_empty = true;

                    /* Resete the error status value */
                    errno = 0;

                    /* Open the file in read mode */
                    file = fopen(path, "r");
                    if (file == NULL) {
                        /* We have an error. Print the error message and exit */
                        if(errno != 0) {
                            perror("fopen");
                        } else {
                            printf("%s: fopen() failed for unknown reason.\n",
                                    kAppName);
                        }

                        exit(EXIT_FAILURE);

                    }

                    /* Check if file is empty */
                    fseek(file, 0, SEEK_END);
                    long fileSize = ftell(file);
                    if (fileSize != 0) {
                        /* File is not empty */
                        is_empty = false;

                    }
                    fclose(file);

                    if (is_empty) {
                        printf("%s: File is empty.\n", kAppName);

                    } else {
                        printf("%s: File is not empty.\n", kAppName);

                    }

                }
                #endif

            }

        }

    }

    return EXIT_SUCCESS;

}


/* ==========================================================================
 * Utility function definitions
 * ========================================================================== */

void short_usage(
        struct argparse *self,
        const struct argparse_option *option
        ) {

    fprintf(stdout, "\
Usage: %s [OPTION]...\n\
Try `%s -h' for more information.\n\
", kAppName, kAppName);

}

void version_info(
        struct argparse *self,
        const struct argparse_option *option
        ) {

    fprintf(stdout, "\
%s 0.1 Copyright (C) yyyy Author Name\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
", kAppName);

}

#ifdef _WIN32
void ReportWin32SystemError(LPSTR lpszAppName, LPTSTR lpszFunction) 
{ 
    /* Retrieve the system error message for the last-error code */
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    /* Display the error message and exit the process */
    fprintf(stderr, "%s: module '%s' failed with error %d: %s\n", lpszAppName,
            lpszFunction, dw, (LPTSTR) &lpMsgBuf);

    /* Free error buffer */
    LocalFree(lpMsgBuf);
}
#endif
