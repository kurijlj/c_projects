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


#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
typedef struct CustomString {
    size_t len;
    char   *data;
} CustomString;


/* ==========================================================================
 * Primitives Declaration Section
 * ========================================================================== */

/* Primitives return values */
typedef enum ReturnValue {
    ExitSuccess = 0,
    MemoryAllocationError = 1,
    OverwriteError = 2,
} ReturnValue;

ReturnValue newCustomString(CustomString *, const size_t);
ReturnValue emptyString(CustomString *);
ReturnValue fromCString(CustomString *, const char *, const size_t);
bool isEmptyString(const CustomString * const);
bool isNullString(const CustomString * const);
void deleteCustomString(CustomString *);


/* ==========================================================================
 * Primitives Definition Section
 * ========================================================================== */

/*
   @brief Creates a new CustomString object and initializes it with the given
          length.

   The newCustomString function allocates memory on the heap for storing
   character data of the CustomString object. It initializes the CustomString
   object with the provided length and assigns the allocated memory to its
   'data' member. Additionally, it appends a new line character '\n' at the end
   of the character array for string termination.

   @param s - Pointer to the CustomString object to be created and initialized.
   @param l - Length of the string to be stored in the CustomString object.

   @return    ReturnValue representing the success or failure of the function.

 */
ReturnValue newCustomString(CustomString *s, const size_t l) {
    /* Validate string structure */
    if(!isNullString(s)) {
        return OverwriteError;

    }

    /* Allocate memory on the heap for storing character data */
    char *data = (char *) calloc(l + 1, sizeof(char));

    /* Check if memory allocation succeeded */
    if(NULL == data) {
        return MemoryAllocationError;

    }

    s->len = l;
    s->data = data;
    s->data[s->len] = '\n';

    return ExitSuccess;

}

ReturnValue emptyString(CustomString *s) {
    return newCustomString(s, 0);

}

/*
   @brief Initializes a CustomString object from a C-style string.

   The fromCString function initializes a CustomString object with the provided
   C-style string and length. It allocates memory for the string data and
   copies the contents of the C-style string into the CustomString object. If
   the length of the C-style string exceeds the specified length, it truncates
   the string to fit within the given length.

   @param s    - Pointer to the CustomString object to be initialized.
   @param cstr - Pointer to the C-style string to be copied into the
                 CustomString object.
   @param l    - Length of the string to be stored in the CustomString object.

   @return     ReturnValue representing the success or failure of the function.

 */
ReturnValue fromCString(CustomString *s, const char *cstr, const size_t l) {
    /* Allocate memory for the string */
    const ReturnValue r = newCustomString(
            s,
            strlen(cstr) > l ? l : strlen(cstr)
            );

    /* Check if memory allocation succeeded */
    if(ExitSuccess != r) {
        return r;

    }

    strncpy(s->data, cstr, s->len);

    return ExitSuccess;

}

/*
   @brief Checks if a CustomString object is empty.

   The isEmptyString function determines whether a CustomString object is
   empty or not. It checks if the length of the CustomString is zero and if the
   data pointer is not NULL. If both conditions are satisfied, it returns true
   indicating that the CustomString is empty. Otherwise, it returns false
   indicating that the CustomString is not empty.

   @param s - Pointer to the CustomString object to be checked for emptiness.

   @return    bool value indicating whether the CustomString is empty (true) or
              not (false).

 */
bool isEmptyString(const CustomString * const s) {
    bool result = false;

    if(0 == s->len && NULL != s->data) {
        result = true;

    }

    return result;

}

/*
   @brief Checks if a CustomString object is a null string.

   The isNullString function determines whether a CustomString object is null
   or not. It checks if the length of the CustomString is zero and if the data
   pointer is NULL. If both conditions are satisfied, it returns true
   indicating that the CustomString is null. Otherwise, it returns false
   indicating that the CustomString is not null.

   @param s - Pointer to the CustomString object to be checked for nullness.

   @return    bool value indicating whether the CustomString is null (true) or
              not (false).

 */
bool isNullString(const CustomString * const s) {
    bool result = false;

    if(0 == s->len && NULL == s->data) {
        result = true;

    }

    return result;

}

/*
   @brief Deletes the content of a CustomString object and releases its
          allocated memory.

   The deleteCustomString function deallocates the memory occupied by the
   character data of a CustomString object. It first checks if the data pointer
   is not NULL, indicating that memory has been allocated. If so, it frees the
   memory using the free function, sets the data pointer to NULL, and resets the
   length to zero. This function effectively deletes the content of the
   CustomString object and ensures proper memory cleanup.

   @param s Pointer to the CustomString object to be deleted.

 */
void deleteCustomString(CustomString *s) {
    if(!isNullString(s)) {
        free(s->data);
        s->data = NULL;
        s->len = 0;

    }

}

#endif
