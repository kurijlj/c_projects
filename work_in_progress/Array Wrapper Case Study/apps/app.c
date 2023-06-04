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
 * Headers include section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */
#include <argparse.h>


/* ==========================================================================
 * Global variables section
 * ========================================================================== */

static const char *const kAppName = "app";
static const char *const kDescription = "\n\
Framework for building CLI apps using \"argparse\".\n\n\
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


/* ==========================================================================
 * Custom data types declarations
 * ========================================================================== */

/*
   @brief Represents a character array structure.

   The CharArray structure is used to store a dynamically allocated character
   array along with its length. It provides a convenient way to manipulate and
   access character data in C.

   @var data - Pointer to the character array.
   @var len  - Length of the character array.

 */
typedef struct CharArray {
    char *data;
    size_t len;

} CharArray;

/*
   @brief Represents a list of CharArray structures.

   The CharArrayList structure is used to store an array of CharArray pointers
   along with the number of elements in the list. It provides a convenient way
   to manage a collection of CharArray objects in C.

   @var list - Pointer to an array of const CharArray pointers.
   @var len  - Number of elements in the list.

*/
typedef struct CharArrayList {
    const CharArray **list;
    size_t len;

} CharArrayList;


/* ==========================================================================
 * Custom functions declarations
 * ========================================================================== */

CharArray *NewCharArray(size_t);
CharArray *ConstCharAsCharArray(const char *, const size_t);
CharArray *CopyCharArray(const CharArray *);
void set_char_at(CharArray *, const size_t, const char);
void free_char_array(CharArray *);
int equal_char_arrays(const CharArray *, const CharArray *);
const char *char_array_as_cstr(const CharArray *);
CharArrayList *NewCharArrayList(size_t);
void set_char_array_at(CharArrayList *, const size_t, const CharArray *);
CharArray *get_char_array_at(CharArrayList *, const size_t);
void free_char_array_list(CharArrayList *);


/* ==========================================================================
 * App's main function body
 * ========================================================================== */

int main(int argc, const char **argv) {

    int usage = 0;
    int version = 0;

    struct argparse_option options[] = {
        OPT_GROUP("general options"),
        OPT_HELP(),
        OPT_BOOLEAN(
                '\0',
                "usage",
                &usage,
                "give a short usage message",
                &short_usage,
                0,
                0
                ),
        OPT_BOOLEAN(
                'V',
                "version",
                &version,
                "print program version",
                &version_info,
                0,
                0
                ),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, kUsages, 0);
    argparse_describe(&argparse, kDescription, kEpilogue);
    argc = argparse_parse(&argparse, argc, argv);

    if (usage != 0 || version != 0) {
        exit(EXIT_SUCCESS);

    }

    if (argc == 0) {
        /* Never ever forget to put const modifier before string literal */
        const char msg1[] = "Convey this message further ...";
        const char *msg2 = "Another message.";
        /* msg[31] = '.';  Very bad of me */
        CharArray *a = NewCharArray(15);
        CharArray *b = ConstCharAsCharArray("Hello World!", strlen("Hello World!"));
        CharArray *c = ConstCharAsCharArray(msg1, strlen(msg1));
        CharArray *d = ConstCharAsCharArray(msg2, strlen(msg2));
        CharArray *e = ConstCharAsCharArray("by Ljubomir Kurij", strlen("by Ljubomir Kurij"));
        CharArray *f = CopyCharArray(e);
        CharArray *g = ConstCharAsCharArray("Zdravo ", strlen("Zdravo "));
        CharArray *h = ConstCharAsCharArray("Svete!", strlen("Svete!"));
        CharArrayList *l = NewCharArrayList(2);
        size_t i = 0;

        /* Populate a */
        while(a->len >= i) {
            set_char_at(a, i, 65 + i);
            i++;
        }

        /* Populate CharArray list */
        set_char_array_at(l, 0, g);
        set_char_array_at(l, 1, h);

        fprintf(stdout, "%s: %s\n", kAppName, char_array_as_cstr(a));
        fprintf(stdout, "%s: %s\n", kAppName, char_array_as_cstr(b));
        fprintf(stdout, "%s: %s\n", kAppName, char_array_as_cstr(c));
        fprintf(stdout, "%s: %s\n", kAppName, char_array_as_cstr(d));
        fprintf(
                stdout,
                "%s: '%s' is equal to '%s': %s\n",
                kAppName,
                char_array_as_cstr(e),
                char_array_as_cstr(a),
                equal_char_arrays(e, a) ? "true" : "false"
                );
        fprintf(
                stdout,
                "%s: '%s' is equal to '%s': %s\n",
                kAppName,
                char_array_as_cstr(e),
                char_array_as_cstr(f),
                equal_char_arrays(e, f) ? "true" : "false"
                );
        fprintf(
                stdout,
                "%s: %s%s\n",
                kAppName,
                char_array_as_cstr(get_char_array_at(l, 0)),
                char_array_as_cstr(get_char_array_at(l, 1))
               );

        free_char_array(a);
        free_char_array(b);
        free_char_array(c);
        free_char_array(d);
        free_char_array(e);
        free_char_array(f);
        free_char_array_list(l);
        g = NULL;
        h = NULL;

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
Usage: app_name [OPTION]...\n\
Try `app_name -h' for more information.\n\
");

}

void version_info(
        struct argparse *self,
        const struct argparse_option *option
        ) {

    fprintf(stdout, "\
app_name 0.1 Copyright (C) yyyy Author Name\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
");

}


/* ==========================================================================
 * Custom functions declarations
 * ========================================================================== */

CharArray *NewCharArray(size_t len) {

    /* Allocate memory on the heap for the structure */
    CharArray *a = (CharArray *) malloc(sizeof(CharArray));

    /* Check if memory allocation succeeded */
    if(NULL == a) {
        return NULL;

    }

    a->len = len;
    a->data = (char *) calloc(a->len + 1, sizeof(char));

    /* Check if memory allocation succeeded */
    if(NULL == a->data){
        free(a);
        return NULL;
    }

    a->data[a->len] = '\0';

    return a;

}

CharArray *ConstCharAsCharArray(const char *str, const size_t n) {

    /* Allocate memory for the array */
    CharArray *a = NewCharArray(strlen(str) > n ? n : strlen(str));

    /* Check if memory allocation succeeded */
    if(NULL == a) {
        return NULL;

    }

    strncpy(a->data, str, a->len);

    return a;

}

CharArray *CopyCharArray(const CharArray *a) {

    /* Allocate memory for the array */
    CharArray *b = NewCharArray(a->len);

    /* Check if memory allocation succeeded */
    if(NULL == a) {
        return NULL;

    }

    strncpy(b->data, a->data, a->len);

    return b;

}

void set_char_at(CharArray *a, const size_t idx, const char c) {
    if(a->len > idx) {
        a->data[idx] = c;

    }

}

void free_char_array(CharArray *a) {

    if(NULL != a) {
        free(a->data);
        free(a);

    }

}

int equal_char_arrays(const CharArray *a, const CharArray *b) {

    if(a->len != b->len) {
        return 0;

    }

    if(0 != strncmp(a->data, b->data, a->len)) {
        return 0;

    }

    return 1;

}

const char *char_array_as_cstr(const CharArray *a) {
    return (const char *) a->data;

}

CharArrayList *NewCharArrayList(size_t len) {

    /* Allocate memory on the heap for the structure */
    CharArrayList *l = (CharArrayList *) malloc(sizeof(CharArrayList));

    /* Check if memory allocation succeeded */
    if(NULL == l) {
        return NULL;

    }

    l->len = len;
    l->list = (CharArray **) calloc(l->len, sizeof(CharArray *));

    /* Check if memory allocation succeeded */
    if(NULL == l->list){
        free(l);
        return NULL;
    }

    size_t i = 0;

    while(l->len > i) {
        l->list[i] = NULL;

        i++;

    }

    return l;

}

void set_char_array_at(CharArrayList *l, const size_t idx, const CharArray *a) {
    if(l->len > idx) {
        l->list[idx] = a;

    }

}

CharArray *get_char_array_at(CharArrayList *l, const size_t idx) {
    if(l->len > idx) {
        return l->list[idx];

    }

    return NULL;

}

void free_char_array_list(CharArrayList *l) {

    if(NULL != l) {
        size_t i = 0;

        while(l->len > i) {
            free_char_array(l->list[i]);
            l->list[i] = NULL;
            i++;

        }
        free(l->list);
        free(l);

    }

}
