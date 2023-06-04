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


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */
#include "heapstring.h"

/* System headers */

/* Standard Library headers */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ==========================================================================
 * Primitives Definition Section
 * ========================================================================== */

HeapString hsinit() {
    HeapString s = {NULL, 0};

    return s;

}

ExitStatus hsnew(HeapString * const s, const size_t l) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer s */
    if (NULL == s) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsnew()' argument `s' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Check if string structure s is initialized to NULL string */
    if (!hsisnull(s)) {
        return esinit(
                HS_OVERWRITE_ATTEMPT,
                "In function `hsnew()' trying to overwrite existing string "
                "data `s'"
                );

    }

    /* Check if requested string length complies with maximum supported string
     * length.
     */
    if (MAX_STR_LEN < l) {
        return esinit(
                HS_MAX_STR_LEN_EXCEED,
                "In function `hsnew()' trying to exceed maximum allowed "
                "string length (argument `l' must have a value < 4096)"
                );

    }

    /* Allocate memory on the heap for storing character data -------------- -*/
    char *data = (char *) calloc(l + 1, sizeof(char));

    /* Check if memory allocation succeeded */
    if (NULL == data) {
        return esinit(
                HS_MEM_ALLOC_ERR,
                "In function `hsnew()' error trying to allocate memory for "
                "the string data `s'"
                );

    }

    /* Assign allocated memory to the string structure ---------------------- */
    s->len = l;
    s->data = data;
    s->data[s->len] = '\0';

    /* No errors occured */
    return esinit(HS_OK, "Function `hsnew()' successfully executed");

}

ExitStatus hsempty(HeapString * const s) {
    /* Allocate memory and initialize empty string -------------------------- */
    ExitStatus status = hsnew(s, 0);

    /* Check if allocation and initialization executed without any error */
    if (HS_OK != status.errcode) {
        /* Function executed unsuccessfully. Format the error messages and
         * terminate further function execution */
        if (HS_INVALID_ARGUMENT == status.errcode) {
            return esinit(
                    HS_INVALID_ARGUMENT,
                    "In function `hsempty()' argument `s' must be a "
                    "pointer to a valid memory location (not a NULL)"
                    );

        } else if (HS_OVERWRITE_ATTEMPT == status.errcode) {
            return esinit(
                    HS_OVERWRITE_ATTEMPT,
                    "In the function `hsempty()' trying to overwrite existing "
                    "string data `s'"
                    );

        } else if (HS_MEM_ALLOC_ERR == status.errcode) {
            return esinit(
                    HS_MEM_ALLOC_ERR,
                    "In the function `hsempty()' error trying to allocate "
                    "memory for the string data `s'"
                    );

        }

    }

    /* No errors occured */
    return esinit(HS_OK, "Function `hsempty()' successfully executed");

}

ExitStatus hsfromcstr(HeapString * const s,
        const char * const cstr, const size_t l) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer cstr */
    if (NULL == cstr) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In the function `hsfromcstr()' argument `cstr' must be a "
                "pointer to a valid memory location (not a NULL)"
                );

    }

    /* Check if requested string length complies with maximum supported string
     * length.
     */
    if (MAX_STR_LEN < l) {
        return esinit(
                HS_MAX_STR_LEN_EXCEED,
                "In function `hsnew()' trying to exceed maximum allowed "
                "string length (argument `l' must have a value < 4096)"
                );

    }

    /* Allocate memory for the string --------------------------------------- */
    size_t lcstr = strnlen_s(cstr, MAX_STR_LEN);

    const ExitStatus status = hsnew(s, lcstr > l ? l : lcstr);

    /* Check if allocation and initialization executed without any error */
    if (HS_OK != status.errcode) {
        /* Function executed unsuccessfully. Format the error messages and
         * terminate further function execution */
        if (HS_INVALID_ARGUMENT == status.errcode) {
            return esinit(
                    HS_INVALID_ARGUMENT,
                    "In the function `hsfrmcstr()' argument `s' must be a "
                    "pointer to a valid memory location (not a NULL)"
                    );

        } else if (HS_OVERWRITE_ATTEMPT == status.errcode) {
            return esinit(
                    HS_OVERWRITE_ATTEMPT,
                    "In the function `hsfromcstr()' trying to overwrite "
                    "existing string data `s'"
                    );

        } else if (HS_MEM_ALLOC_ERR == status.errcode) {
            return esinit(
                    HS_MEM_ALLOC_ERR,
                    "In the function `hsfromcstr()' error trying to allocate "
                    "memory for the string data `s'"
                    );

        }

    }

    strncpy(s->data, cstr, s->len);

    /* No errors occured */
    return esinit(HS_OK, "In the function `hsfromcstr()' execution successful");

}

bool hsisempty(const HeapString * const s) {
    bool result = false;

    if (NULL != s) {
        if(0 == s->len && NULL != s->data) {
            result = true;

        }

    }

    return result;

}

bool hsisnull(const HeapString * const s) {
    bool result = false;

    if(NULL != s) {
        if(0 == s->len && NULL == s->data) {
            result = true;

        }

    }

    return result;

}

void hsdelete(HeapString * const s) {
    if(NULL != s && !hsisnull(s)) {
        free(s->data);
        s->data = NULL;
        s->len = 0;

    }

}

size_t hslen(const HeapString * const s) {
    size_t len = 0;

    if(NULL != s && !hsisnull(s)) {
        len = s->len;

    }

    return len;

}

ExitStatus hssubstr(HeapString * const d, const HeapString * const s,
        const size_t i, const size_t l) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer `d' */
    if (NULL == s) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hssubstr()' argument `d' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Validate pointer `s' */
    if (NULL == s) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hssubstr()' argument `s' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Check if string structure `d' is initialized to NULL string */
    if (!hsisnull(d)) {
        return esinit(
                HS_OVERWRITE_ATTEMPT,
                "In function `hsnew()' trying to overwrite existing string "
                "data `d' "
                );

    }

    /* Check if string structure `s' is initialized to NULL string */
    if (hsisnull(s)) {
        return esinit(
                HS_NULL_OP_ATTEMPT,
                "In function `hssubstr()' trying to substring a null string `s'"
                );

    }

    /* Check if index `i' is within a indexable range of the string `s' */
    if(i >= s->len) {
        return esinit(
                HS_INDEX_OUT_OF_RANGE,
                "In function `hssubstr()' trying to access index out of range"
                "of indexes of string `s'"
                );

    }

    /* Check if substring's length `l' is within a indexable range of the
     * string `s' */
    if(i + l >= s->len) {
        return esinit(
                HS_SUBSTRING_TOO_LONG,
                "In function `hssubstr()' trying to substring past the length "
                "of string `s'"
                );

    }

    /* Allocate memory on the heap for the `d''s character data ------------ -*/
    char *data = (char *) calloc(l + 1, sizeof(char));

    /* Check if memory allocation succeeded */
    if (NULL == data) {
        return esinit(
                HS_MEM_ALLOC_ERR,
                "In function `hssubstr()' error trying to allocate memory for "
                "the string data `d'"
                );

    }

    /* Copy charcter data from  `s' to `d' ---------------------------------- */
    d->len = l;
    d->data[d->len] = '\0';
    memcpy(d->data, s->data + i, l);

    /* No errors occured */
    return esinit(HS_OK, "Function `hssubstr()' successfully executed");

}

ExitStatus hsconcat(HeapString * const d, const HeapString * const sa,
        const HeapString * const sb) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer `sa' */
    if (NULL == sa) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsconcat()' argument `sa' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Validate pointer `sb' */
    if (NULL == sb) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsconcat()' argument `sb' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Check if string structure `s' is initialized to NULL string */
    if (hsisnull(sa)) {
        return esinit(
                HS_NULL_OP_ATTEMPT,
                "In function `hssubstr()' trying to concatenate uninitialized"
                "string `sa'"
                );

    }

    /* Check if string structure `p' is initialized to NULL string */
    if (hsisnull(sb)) {
        return esinit(
                HS_NULL_OP_ATTEMPT,
                "In function `hssubstr()' trying to concatenate uninitialized"
                "string `sb'"
                );

    }


    /* No errors occured */
    return esinit(HS_OK, "Function `hsconcat()' successfully executed");

}
