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
#include <gsl/gsl_math.h>


/* ==========================================================================
 * Macros definitions section
 * ========================================================================== */

#define APP_NAME             "app_name"
#define APP_VERSION          "0.1"
#define APP_AUTHOR           "Author Name"
#define APP_EMAIL            "author@email.com"
#define APP_COPYRIGHT_YEAR   "yyyy"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE          "GPLv3+"
#define APP_LICENSE_URL      "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION      "<one line to give the program's name "\
                             "and a brief idea of what it does.>"
#define APP_USAGE_A          "app_name [OPTION]..."
#define APP_EPILOGUE         "Report bugs to <" APP_EMAIL ">."


/* ==========================================================================
 * Global variables section
 * ========================================================================== */

static const char *const kUsages[] = {
    APP_USAGE_A,
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
        printf("Main module running ...\n");
        printf("PI = %f\n", M_PI);

    }

    return EXIT_SUCCESS;

}


/* ==========================================================================
 * Utility function definitions
 * ========================================================================== */

void short_usage(struct argparse *self, const struct argparse_option *option) {
    fprintf(stdout, "%s %s\n%s\n",
        "Usage:", APP_USAGE_A,
        "Try `app_name -h' for more information."
        );

}

void version_info(struct argparse *self, const struct argparse_option *option) {
    fprintf(stdout, "%s %s %s %s %s\n%s %s: %s <%s>\n%s\n%s\n",
            APP_NAME, APP_VERSION, "Copyright (c)",
            APP_COPYRIGHT_YEAR, APP_AUTHOR,
            "License", APP_LICENSE, "GNU GPL version 3 or later",
            APP_LICENSE_URL,
            "This is free software: you are free "
            "to change and redistribute it.",
            "There is NO WARRANTY, to the extent permitted by law."
            );

}
