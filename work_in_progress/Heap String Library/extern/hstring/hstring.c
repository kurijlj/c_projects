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
#include "hstring.h"

/* System headers */

/* Standard Library headers */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ==========================================================================
 * Auxiliary Functions Section
 * ========================================================================== */

size_t _calcbufsize(const size_t slen) {
    size_t bufsz = HSTRING_MIN_BUF_SIZE;

    if(HSTRING_MIN_BUF_SIZE <= slen) {
        div_t r = div(slen, HSTRING_MIN_BUF_SIZE);

        bufsz = (size_t) HSTRING_MIN_BUF_SIZE * (r.quot + 1);

    }

    return bufsz;

}


/* ==========================================================================
 * Primitives Definition Section
 * ========================================================================== */

HString hsnew() {
    HString s = {NULL, 0, 0};

    return s;

}

ExitStatus hsinit(HString * const str, const char * const init, size_t len) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer str */
    if (NULL == str) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsinit()' argument `str' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Validate pointer init */
    if (NULL == init) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsinit()' argument `init' must be a valid string "
                "literal (not a NULL)"
                );

    }

    /* Check if requested string length complies with maximum supported buffer
     * size for the string data (set by HSTRING_MAX_BUF_SIZE).
     */
    if (HSTRING_MAX_BUF_SIZE <= len) {
        return esinit(
                HS_MAX_STR_LEN_EXCEED,
                "In function `hsinit()' trying to exceed maximum supported "
                "string buffer size (argument `len' must have a value < "
                "HSTRING_MAX_BUF_SIZE)"
                );

    }

    /* Calculate number of bytes required for storing `init' data. If the length
     * of the `init' exceeds value supplied for len, use len. Otherwise use
     * strlen(init)
     */
    size_t initlen = strnlen_s(init, HSTRING_MAX_BUF_SIZE);
    len = initlen > len ? len : initlen;

    /* Allocate memory on the heap for the string data -----------------------*/
    size_t allocated_len = _calcbufsize(len);
    char *databuf = (char *) calloc(allocated_len, sizeof(char));

    /* Check if memory allocation succeeded */
    if (NULL == databuf) {
        return esinit(
                HS_MEM_ALLOC_ERR,
                "In function `hsinit()' error trying to allocate memory for "
                "the string `str'"
                );

    }

    /* Assign allocated memory to `str' ------------------------------------- */
    str->len = len;
    str->allocated_len = allocated_len;
    str->data = databuf;
    str->data[str->len + 1] = '\0';

    /* Copy character data from `init' to `dest' ----------------------------- */
    memcpy(str->data, init, str->len);

    /* Exit with no errors -------------------------------------------------- */
    return esinit(HS_OK, "Function `hsinit()' successfully executed");

}

ExitStatus hscopy(HString * const dest, const HString * const src) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer dest */
    if (NULL == dest) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hscopy()' argument `dest' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Validate pointer src */
    if (NULL == src) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hscopy()' argument `src' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Check if `dest' is already intialized -------------------------------- */
    if (hsisinit(dest)) {
        return esinit(
                HS_OVERWRITE_ATTEMPT,
                "In function `hscopy()' trying to overwrite existing "
                "string `dest'"
                );

    }

    /* Check if `src' is already intialized -------------------------------- */
    if (!hsisinit(src)) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hscopy()' trying to copy uninitialized "
                "string `src'"
                );

    }

    /* Allocate memory on the heap for the string data ---------------------- */
    char *databuf = (char *) calloc(src->allocated_len, sizeof(char));

    /* Check if memory allocation succeeded */
    if (NULL == databuf) {
        return esinit(
                HS_MEM_ALLOC_ERR,
                "In function `hscopy()' error trying to allocate memory for "
                "the `dest'"
                );

    }

    /* Assign allocated memory to `dest' ------------------------------------ */
    dest->len = src->len;
    dest->allocated_len = src->allocated_len;
    dest->data = databuf;
    dest->data[dest->len + 1] = '\0';

    /* Copy character data from `src' to `dest' ----------------------------- */
    memcpy(dest->data, src->data, src->len);

    /* Exit with no errors -------------------------------------------------- */
    return esinit(HS_OK, "Function `hscopy()' successfully executed");

}

bool hsisinit(const HString * const str) {
    bool result = false;

    if (NULL != str) {
        if (NULL != str->data && 0 != str->allocated_len) {
            result = true;

        }

    }

    return result;

}

bool hsisempty(const HString * const str) {
    bool result = false;

    if (NULL != str) {
        if (hsisinit(str) && 0 == str->len) {
            result = true;

        }

    }

    return result;

}

void hsfree(HString * const str) {
    if(NULL != str && hsisinit(str)) {
        free(str->data);
        str->data = NULL;
        str->len = 0;
        str->allocated_len = 0;

    }

}

size_t hslen(const HString * const str) {
    size_t len = 0;

    if(NULL != str && hsisinit(str)) {
        len = str->len;

    }

    return len;

}

ExitStatus hssubstr(HString * const dest, const HString * const src,
        const size_t idx, const size_t len) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer `dest' */
    if (NULL == dest) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hssubstr()' argument `dest' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Validate pointer `src' */
    if (NULL == src) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hssubstr()' argument `src' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Check if `dest' is already intialized -------------------------------- */
    if (hsisinit(dest)) {
        return esinit(
                HS_OVERWRITE_ATTEMPT,
                "In function `hssubstr()' trying to overwrite existing "
                "string `dest'"
                );

    }

    /* Check if `src' is already intialized -------------------------------- */
    if (!hsisinit(src)) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hssubstr()' trying to substring "
                "uninitialized string `src'"
                );

    }

    /* Check if index `idx' is within a indexable range of the `src' data */
    if(idx > src->len) {
        return esinit(
                HS_INDEX_OUT_OF_RANGE,
                "In function `hssubstr()' trying to access data beyond index "
                "range of `src'"
                );

    }

    /* Check if substring's length `len' is within a range of data of `src' */
    if(idx + len > src->len) {
        return esinit(
                HS_SUBSTR_OUT_OF_RANGE,
                "In function `hssubstr()' trying to substring past the length "
                "of `src'"
                );

    }

    /* Allocate memory on the heap for the string data ---------------------- */
    size_t allocated_len = _calcbufsize(len);
    char *databuf = (char *) calloc(allocated_len, sizeof(char));

    /* Check if memory allocation succeeded */
    if (NULL == databuf) {
        return esinit(
                HS_MEM_ALLOC_ERR,
                "In function `hssubstr()' error trying to allocate memory for "
                "the `dest'"
                );

    }

    /* Copy character data from `src' to `dest' ----------------------------- */
    dest->len = len;
    dest->allocated_len = allocated_len;
    dest->data = databuf;
    dest->data[dest->len] = '\0';
    memcpy(dest->data, src->data + idx, len);

    /* Exit with no errors */
    return esinit(HS_OK, "Function `hssubstr()' successfully executed");

}

ExitStatus hsconcat(HString * const dest, const HString * const srca,
        const HString * const srcb) {
    /* Validate input arguments --------------------------------------------- */

    /* Validate pointer `dest' */
    if (NULL == dest) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsconcat()' argument `dest' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Validate pointer `srca' */
    if (NULL == srca) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsconcat()' argument `srca' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Validate pointer `srcb' */
    if (NULL == srcb) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hsconcat()' argument `srcb' must be a pointer to "
                "a valid memory location (not a NULL)"
                );

    }

    /* Check if `dest' is already intialized -------------------------------- */
    if (hsisinit(dest)) {
        return esinit(
                HS_OVERWRITE_ATTEMPT,
                "In function `hsconcat()' trying to overwrite existing "
                "string `dest'"
                );

    }

    /* Check if `srca' is already intialized -------------------------------- */
    if (!hsisinit(srca)) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hssubstr()' trying to concatenate "
                "uninitialized string `srca'"
                );

    }

    /* Check if `srcb' is already intialized -------------------------------- */
    if (!hsisinit(srcb)) {
        return esinit(
                HS_INVALID_ARGUMENT,
                "In function `hssubstr()' trying to concatenate "
                "uninitialized string `srcb'"
                );

    }

    /* Check if required string length complies with maximum supported buffer
     * size for the string data (set by HSTRING_MAX_BUF_SIZE).
     */
    size_t len = srca->len + srcb->len;

    if (HSTRING_MAX_BUF_SIZE <= len) {
        return esinit(
                HS_MAX_STR_LEN_EXCEED,
                "In function `hsconcat()' trying to exceed maximum supported "
                "string buffer size (hslen(srca + srcb) must be "
                "< HSTRING_MAX_BUF_SIZE)"
                );

    }

    /* Allocate memory on the heap for the concatenated string ------------- -*/
    size_t allocated_len = _calcbufsize(len);
    char *databuf = (char *) calloc(allocated_len, sizeof(char));

    /* Check if memory allocation succeeded */
    if (NULL == databuf) {
        return esinit(
                HS_MEM_ALLOC_ERR,
                "In function `hsconcat()' error trying to allocate memory for "
                "the `dest'"
                );

    }

    /* Copy charcter data from  `s' to `d' ---------------------------------- */
    dest->len = len;
    dest->allocated_len = allocated_len;
    dest->data = databuf;
    dest->data[dest->len] = '\0';
    memcpy(dest->data, srca->data, srca->len);
    memcpy(dest->data + srca->len, srcb->data, srcb->len);

    /* Exit with no errors */
    return esinit(HS_OK, "Function `hsconcat()' successfully executed");

}

ExitStatus hsindex(const HString * const str, const HString * const pat) {

    /* Exit with no errors */
    return esinit(HS_OK, "Function `hsindex()' successfully executed");

}
