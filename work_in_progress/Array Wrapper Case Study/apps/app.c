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

void short_usage(struct argparse *self, const struct argparse_option *option);
void version_info(struct argparse *self, const struct argparse_option *option);


/* ==========================================================================
 * Custom data types declarations
 * ========================================================================== */

typedef struct chararray {
    char *data;
    size_t len;

} CharArray;


/* ==========================================================================
 * Custom functions declarations
 * ========================================================================== */

CharArray *NewCharArray(size_t len);
void set_char_at(CharArray *a, size_t idx, char c);
void free_char_array(CharArray *a);


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
        CharArray *a = NewCharArray(15);

        for(size_t i=0; i < 15; i++) {
            set_char_at(a, i, 65 + i);

        }

        fprintf(stdout, "%s: %s", kAppName, a->data);

        free_char_array(a);

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
    a->data = (char *) calloc(len + 2, sizeof(char));

    /* Check if memory allocation succeeded */
    if(NULL == a->data){
        free(a);
        return NULL;
    }

    a->data[a->len + 0] = '\n';
    a->data[a->len + 1] = '\0';

    return a;

}

void set_char_at(CharArray *a, size_t idx, char c) {
    if(a->len > idx) {
        a->data[idx] = c;

    }

}

void free_char_array(CharArray *a) {

    free(a->data);
    free(a);

}
