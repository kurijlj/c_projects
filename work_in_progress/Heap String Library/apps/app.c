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
#include <exitstatus.h>
#include <hstring.h>


/* ==========================================================================
 * Global variables section
 * ========================================================================== */

static const char *const kAppName = "app";
static const char *const kDescription = "\n\
Main module for testing \"Heap String Library\".\n\n\
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
        printf("%s: Main module is running ...\n", kAppName);

        HString s1 = hsnew(), s2 = hsnew(), s3 = hsnew();
        HString *ps1 = malloc(sizeof(HString));
        *ps1 = hsnew();

        ExitStatus status = hsinit(&s1, "Hello World!",
                HSTRING_MAX_BUF_SIZE - 1);
        if(HS_OK != status.errcode) {
            fprintf(
                    stderr,
                    "%s: ERROR(%d): %s\n",
                    kAppName,
                    status.errcode,
                    status.msg
                   );

            /* Clean up */
            hsfree(&s1);
            hsfree(&s2);
            hsfree(&s3);
            hsfree(ps1);
            if(NULL != ps1) {
                free(ps1);

            }

            /* Exit with error */
            exit(EXIT_FAILURE);

        }

        status = hsinit(&s2, " Hello C!", HSTRING_MAX_BUF_SIZE - 1);
        if(HS_OK != status.errcode) {
            fprintf(
                    stderr,
                    "%s: ERROR(%d): %s\n",
                    kAppName,
                    status.errcode,
                    status.msg
                   );

            /* Clean up */
            hsfree(&s1);
            hsfree(&s2);
            hsfree(&s3);
            hsfree(ps1);
            if(NULL != ps1) {
                free(ps1);

            }

            /* Exit with error */
            exit(EXIT_FAILURE);

        }

        status = hsconcat(&s3, &s1, &s2);
        if(HS_OK != status.errcode) {
            fprintf(
                    stderr,
                    "%s: ERROR(%d): %s\n",
                    kAppName,
                    status.errcode,
                    status.msg
                   );

            /* Clean up */
            hsfree(&s1);
            hsfree(&s2);
            hsfree(&s3);
            hsfree(ps1);
            if(NULL != ps1) {
                free(ps1);

            }

            /* Exit with error */
            exit(EXIT_FAILURE);

        }

        status = hscopy(ps1, &s1);
        if(HS_OK != status.errcode) {
            fprintf(
                    stderr,
                    "%s: ERROR(%d): %s\n",
                    kAppName,
                    status.errcode,
                    status.msg
                   );

            /* Clean up */
            hsfree(&s1);
            hsfree(&s2);
            hsfree(&s3);
            hsfree(ps1);
            if(NULL != ps1) {
                free(ps1);

            }

            /* Exit with error */
            exit(EXIT_FAILURE);

        }
    
        printf("%s: `%s'\n", kAppName, s1.data);
        printf("%s: `%s'\n", kAppName, s2.data);
        printf("%s: `%s'\n", kAppName, s3.data);
        printf("%s: `%s'\n", kAppName, ps1->data);

        hsfree(&s1);
        hsfree(&s2);
        hsfree(&s3);
        hsfree(ps1);
        if(NULL != ps1) {
            free(ps1);

        }

        printf("%s: Execution successful!\n", kAppName);

    }

    return EXIT_SUCCESS;

}


/* ==========================================================================
 * Utility function definitions
 * ========================================================================== */

/**
 * @brief Print a short usage message.
 *
 * @param self The argparse structure.
 * @param option The option structure.
 *
 * @return None.
 *
 * @details This function is called when the user specifies the '--usage' or
 * '-usage' option. It prints a short usage message and exits.
 */
void short_usage(
        struct argparse *self,
        const struct argparse_option *option
        ) {

    fprintf(stdout, "\
Usage: app_name [OPTION]...\n\
Try `app_name -h' for more information.\n\
");

}

/**
 * @brief Print version information.
 *
 * @param self The argparse structure.
 * @param option The option structure.
 *
 * @return None.
 *
 * @details This function is called when the user specifies the '--version' or
 * '-V' option. It prints version information and exits.
 */
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
