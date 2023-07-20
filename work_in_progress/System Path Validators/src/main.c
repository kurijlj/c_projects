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
#include <spvalid.h>


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


/* ==========================================================================
 * Main module
 * ========================================================================== */

int main(int argc, const char **argv) {

    int usage = 0;
    int version = 0;
    char * path = NULL;

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

        if(NULL == path) {
            path = "\0";
        }

        ps_flags_t path_status = check_path_status(path);

        printf("%s: Path: %s\n", kAppName, path);
        printf("%s: Path status: \n", kAppName);
        printBits(path_status);

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