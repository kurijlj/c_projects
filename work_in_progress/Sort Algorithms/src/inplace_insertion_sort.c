/* ==========================================================================
 * inplace_insertion_sort - Implementation of inplace insertion sort algorithm.
 *
 *  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
 * 2023-06-19 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * inplace_insertion_sort.c: created.
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
#include <gsl/gsl_rng.h>
#include <gsl/gsl_errno.h>


/* ==========================================================================
 * Global variables section
 * ========================================================================== */

static const char *const kAppName = "inplace_insertion_sort";
static const char *const kDescription = "\n\
Implementation of in-place insertion sort algorithm.\n\n\
Mandatory arguments to long options are mandatory for short options too.";
static const char *const kEpilogue = "\n\
Report bugs to <author@email.com>.";
static const char *const kUsages[] = {
    "inplace_insertion_sort [OPTION]...",
    "inplace_insertion_sort ...",
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
    int number = 0;
    int seed = 0;
    char * const generator = NULL;

    struct argparse_option options[] = {
        OPT_GROUP("General options"),
        OPT_HELP(),
        OPT_BOOLEAN('\0', "usage", &usage, "give a short usage message",
            &short_usage, 0, 0),
        OPT_BOOLEAN('V', "version", &version, "print program version",
            &version_info, 0, 0),
        OPT_GROUP("Generator options"),
        OPT_INTEGER('n', "number", &number,
            "number of random numbers to generate", NULL, 0, 0),
        OPT_STRING('g', "generator", &generator, "random number generator",
            NULL, 0, 0),
        OPT_INTEGER('s', "seed", &seed, "seed for random number generator",
            NULL, 0, 0),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, kUsages, 0);
    argparse_describe(&argparse, kDescription, kEpilogue);
    argc = argparse_parse(&argparse, argc, argv);

    if (argc != 0) {
        /* User supplied an option that is not defined */
        printf("%s: Unknown command line option: %s\n", kAppName, argv[0]);
        short_usage(&argparse, NULL);

        exit(EXIT_FAILURE);

    } else {
        printf("%s Main module running ...\n", kAppName);
        printf("%s: Generator: %s\n", kAppName, generator);
        printf("%s: Seed: %d\n", kAppName, seed);
        printf("%s: Number of random numbers: %d\n", kAppName, number);

    }

    return EXIT_SUCCESS;

}


/* ========================================================================== *
 * Utility function definitions
 * ========================================================================== */

void short_usage(
        struct argparse *self,
        const struct argparse_option *option
        ) {

    fprintf(stdout, "\
Usage: inplace_insertion_sort  [OPTION]...\n\
Try `inplace_insertion_sort  -h' for more information.\n\
");

    exit(EXIT_SUCCESS);

}

void version_info(
        struct argparse *self,
        const struct argparse_option *option
        ) {

    fprintf(stdout, "\
inplace_insertion_sort 0.1 Copyright (C) 2023 Author Name\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
");

    exit(EXIT_SUCCESS);

}

/* ------------------------------------------------------------------------- *
 * Function: validate_rng_generator
 *
 * Validate the user supplied generator name against the names of all the
 * generators in the library.
 * 
 * Parameters:
 * * self: argparse object
 * * option: argparse option
 * 
 * Returns:
 * * void
 * -------------------------------------------------------------------------- */
void validate_rng_generator(
        struct argparse *self,
        const struct argparse_option *option
    ) {
    if (option->value) {
        const gsl_rng_type **t, **t0 = gsl_rng_types_setup ();

        gsl_rng_default = 0;

        /* Check user supplied generator name against the names of all
           the generators 
         */
        for (t = t0; *t != 0; t++) {
            if (0 == strcmp (option->value, (*t)->name)) {
                gsl_rng_default = *t;

                break;

            }

        }

        if (0 == gsl_rng_default) {
            int i = 0;

            fprintf (stderr, "GSL_RNG_TYPE=%s not recognized\n", option->value);
            fprintf (stderr, "Valid generator types are:\n");

            for (t = t0; *t != 0; t++) {
                fprintf (stderr, " %18s", (*t)->name);

                if (0 == (++i) % 4) {
                    fputc ('\n', stderr);

                }

            }

            fputc ('\n', stderr);
            GSL_ERROR_VAL ("unknown generator", GSL_EINVAL, 0);

            exit(EXIT_FAILURE);

        }

    }

}