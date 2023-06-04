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
 * ========================================================================== */


#ifndef HEAPSTRING_H
#define HEAPSTRING_H

/* ==========================================================================
 * Define's section
 * ========================================================================== */

#define MAX_STR_LEN 4096 - 1  /* Maximum supported string length */


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */
#include <exitstatus.h>

/* System headers */

/* Standard Library headers */
#include <stdbool.h>


/* ==========================================================================
 * Abstract Data Type Definition Section
 * ========================================================================== */

/*
   @brief String representation using an variable-aggregate abstract data type.

   The CustomString structure is used to store a string along with its length.
   It provides a convenient way to manage and manipulate strings in C. Memory
   for storing characters is allocated on the heap. It uses newline character
   to terminate the string.

   @var len  - Length of the string.
   @var data - Pointer to the character array that holds the string data.

 */
typedef struct {
    char   *data;
    size_t len;
} HeapString;


/* ==========================================================================
 * Error Codes Definition Section
 * ========================================================================== */

typedef enum {
    HS_OK = 0,
    HS_INVALID_ARGUMENT = 1,
    HS_OVERWRITE_ATTEMPT = 2,
    HS_MAX_STR_LEN_EXCEED = 3,
    HS_MEM_ALLOC_ERR = 4,
    HS_NULL_OP_ATTEMPT = 5,
    HS_INDEX_OUT_OF_RANGE = 6,
    HS_SUBSTRING_TOO_LONG = 7,
} HS_ErrorCode;

/* ==========================================================================
 * Primitives Declaration Section
 * ========================================================================== */

HeapString hsinit();
ExitStatus hsnew(HeapString * const, const size_t);
ExitStatus hsempty(HeapString * const);
ExitStatus hsfromcstr(HeapString * const, const char *const, const size_t);
bool hsisempty(const HeapString * const);
bool hsisnull(const HeapString * const);
void hsdelete(HeapString * const);

size_t hslen(const HeapString * const);
ExitStatus hssubstr(HeapString * const, const HeapString * const,
        const size_t, const size_t);
ExitStatus hsconcat(HeapString * const, const HeapString * const,
        const HeapString * const);

#endif
