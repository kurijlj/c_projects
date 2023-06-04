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


#ifndef HSTRING_H
#define HSTRING_H

/* ==========================================================================
 * Define's section
 * ========================================================================== */

#define HSTRING_MIN_BUF_SIZE 32
#define HSTRING_MAX_BUF_SIZE 32 * 128 /* i.e. 4096 */


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

typedef struct {
    char   *data;
    size_t len;
    size_t allocated_len;
} HString;


/* ==========================================================================
 * Error Codes Definition Section
 * ========================================================================== */

typedef enum {
    HS_OK = 0,
    HS_INVALID_ARGUMENT = 1,
    HS_OVERWRITE_ATTEMPT = 2,
    HS_MAX_STR_LEN_EXCEED = 3,
    HS_MEM_ALLOC_ERR = 4,
    HS_INDEX_OUT_OF_RANGE = 5,
    HS_SUBSTR_OUT_OF_RANGE = 6,
} HS_ErrorCode;


/* ==========================================================================
 * Primitives Declaration Section
 * ========================================================================== */

HString hsnew();
ExitStatus hsinit(HString * const, const char * const, const size_t);
ExitStatus hscopy(HString * const, const HString * const);
bool hsisempty(const HString * const);
bool hsisinit(const HString * const);
void hsfree(HString * const);

size_t hslen(const HString * const);
ExitStatus hssubstr(HString * const, const HString * const,
        const size_t, const size_t);
ExitStatus hsconcat(HString * const, const HString * const,
        const HString * const);
ExitStatus hsindex(const HString * const, const HString * const);

#endif
