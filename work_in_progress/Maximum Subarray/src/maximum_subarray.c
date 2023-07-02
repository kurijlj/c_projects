/* ========================================================================== *
 * maximum_subarray - Implementation of the maximum subarray algorithm
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


/* ========================================================================== *
 *
 * 2023-07-01 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * maximum_subarray.c: created.
 *
 * ========================================================================== */


/* ========================================================================== *
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


/* ========================================================================== *
 * Headers include section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* External libraries headers */
#include <argparse.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_errno.h>


/* ========================================================================== *
 * Global variables section
 * ========================================================================== */

static const char *const kAppName = "maximum_subarray";
static const char *const kDescription = "\n"
    "Implementation of the maximum subarray algorithm.\n\n"
    "Mandatory arguments to long options are mandatory for short options too.";
static const char *const kEpilogue = "\n"
    "Report bugs to <ljubomir_kurij@protonmail.com>.";
static const char *const kUsages[] = {
    "maximum_subarray [OPTION]...",
    "maximum_subarray ...",
    NULL,
};


/* ========================================================================== *
 * Utility function declarations
 * ========================================================================== */

void short_usage (struct argparse *self,
        const struct argparse_option *option);
void version_info (struct argparse *self,
        const struct argparse_option *option);


/* ========================================================================== *
 * Maximum subarray algorithm function declarations
 * ========================================================================== */

long int maximum_subarray (const long int *array, const size_t start,
        const size_t end, size_t *left, size_t *right);
long int maximum_crossing_subarray (const long int *array, size_t start,
        size_t mid, size_t end, size_t *left, size_t *right);


/* ========================================================================== *
 * Main module
 * ========================================================================== */

int main (int argc, const char **argv) {

    int usage   = 0;
    int version = 0;
    int number  = 20;
    int seed    = 123;
    char * const generator = NULL;

    struct argparse_option options[] = {
        OPT_GROUP ("General options"),
        OPT_HELP (),
        OPT_BOOLEAN ('\0', "usage", &usage, "give a short usage message",
            &short_usage, 0, 0),
        OPT_BOOLEAN ('V', "version", &version, "print program version",
            &version_info, 0, 0),
        OPT_GROUP ("Generator options"),
        OPT_INTEGER ('n', "number", &number,
            "number of random numbers to generate", NULL, 0, 0),
        OPT_STRING ('g', "generator", &generator, "random number generator",
            NULL, 0, 0),
        OPT_INTEGER ('s', "seed", &seed, "seed for random number generator",
            NULL, 0, 0),
        OPT_END (),
    };

    struct argparse argparse;
    argparse_init (&argparse, options, kUsages, 0);
    argparse_describe (&argparse, kDescription, kEpilogue);
    argc = argparse_parse (&argparse, argc, argv);

    if (usage != 0 || version != 0) {
        exit(EXIT_SUCCESS);

    }

    if (argc != 0) {
        /* User supplied an option that is not defined */
        printf ("%s: Unknown command line option: %s\n", kAppName, argv[0]);
        short_usage (&argparse, NULL);

        exit (EXIT_FAILURE);

    } else {
        const gsl_rng_type *T = NULL;

        if (NULL != generator) {
            const gsl_rng_type **t, **t0 = gsl_rng_types_setup ();

            /* check GSL_RNG_TYPE against the names of all the generators */
            for (t = t0; *t != 0; t++) {
                if (strcmp (generator, (*t)->name) == 0) {
                    T = *t;
                    break;

                }

            }

            if (NULL == T) {
                int i = 0;

                fprintf (stderr, "GSL_RNG_TYPE=%s not recognized\n", generator);
                fprintf (stderr, "Valid generator types are:\n");

                for (t = t0; *t != 0; t++) {
                    fprintf (stderr, " %18s", (*t)->name);

                    if ((++i) % 4 == 0) {
                        fputc ('\n', stderr);

                    }

                }

                exit (EXIT_FAILURE);

            }

        } else {
            T = gsl_rng_mt19937;

        }

        /* We have an valid geneator name so create a generator chosen by
           the user, or use default one */
        gsl_rng *r = gsl_rng_alloc (T);
        /* gsl_rng_set (r, seed); */
        gsl_rng_set (r, time (NULL));

        /* Initialize the array of random numbers */
        long int *array = malloc (number * sizeof (long int));
        for (size_t i = 0; i < number; i++) {
            int sign =
                (gsl_rng_uniform_int (r, 101) < 51) ? -1 : 1;
            *(array + i) =
                (long int) sign * (long int) gsl_rng_uniform_int (r, 101);

        }
    
        printf ("%s Main module running ...\n", kAppName);
        printf ("%s: Generator: %s\n", kAppName, T->name);
        printf ("%s: Seed: %d\n", kAppName, seed);
        printf ("%s: Array size: %d\n", kAppName, number);
        printf ("%s: Array:\n", kAppName);
        for (size_t i = 0; i < number; i++) {
            /* Here i want to print long int value */
            printf ("%ld", *(array + i));
            if(i < number - 1) {
                printf (",");

            }

        }
        printf ("\n");

        /* Find maximum subarray */
        size_t start = 0;
        size_t end = number - 1;
        long int sum = maximum_subarray (array, 0, number - 1, &start, &end);

        printf ("%s: Maximum subarray:\n", kAppName);
        for (size_t i = start; i <= end; i++) {
            printf ("%ld", *(array + i));
            if(i < end) {
                printf (",");

            }

        }
        printf ("\n");
        printf ("%s: Start: %lu\n", kAppName, (unsigned long int) start);
        printf ("%s: End: %lu\n", kAppName, (unsigned long int) end);
        printf ("%s: Sum: %ld\n", kAppName, sum);

        printf ("%s: End of execution\n", kAppName);


        free (array);
        gsl_rng_free (r);

    }

    return EXIT_SUCCESS;

}


/* ========================================================================== *
 * Utility function definitions
 * ========================================================================== */

void short_usage (struct argparse *self,
        const struct argparse_option *option) {
    fprintf (stdout, "Usage: maximum_subarray  [OPTION]...\n"
        "Try `inplace_insertion_sort  -h' for more information.\n"
        );

}

void version_info (struct argparse *self,
        const struct argparse_option *option) {
    fprintf (stdout, "maximum_subarray 0.1 Copyright (C) 2023 "
        "Author Name\n"
        "License GPLv3+: GNU GPL version 3 or later "
        "<http://gnu.org/licenses/gpl.html>\n"
        "This is free software: you are free to change and redistribute it.\n"
        "There is NO WARRANTY, to the extent permitted by law.\n"
        );

}


/* ========================================================================== *
 * Maximum subarray algorithm function definitions
 * ========================================================================== */

/* -------------------------------------------------------------------------- *
 * Function 'maximum_subarray'
 * --------------------------------------------------------------------------
 * 
 * This function implements the maximum subarray algorithm. It is a recursive
 * function that uses the divide and conquer paradigm.
 * 
 * Parameters:
 *     array: Pointer to the array of long integers.
 *     start: Index of the first element of the array to start searching
 *     subarray for.
 *     end: Index of the last element of the array to end searching
 *     subarray for. 
 *     sub_start: Pointer to the index of the first element of the
 *     maximum subarray.
 *     sub_end: Pointer to the index of the last element of the
 *     maximum subarray.
 * 
 * Returns:
 *     The sum of the maximum subarray.
 * 
 * Notes:
 *    The function assumes that the array has at least one element.
 * 
 * Example:
 *    long int array[] = { 1, 2, 3, 4, 5 };
 *    size_t start = 0;
 *    size_t end = 4;
 *    size_t sub_start;
 *    size_t sub_end;
 *    long int sum = maximum_subarray (array, start, end, &sub_start, &sub_end);
 * 
 * -------------------------------------------------------------------------- */
long int maximum_subarray (const long int *array, const size_t start,
        const size_t end, size_t *sub_start, size_t *sub_end) {
    if (end == start) {
        *sub_start = *sub_end = start;
        return *(array + start);

    } else {
        size_t mid             = start + (end - start) / 2;
        size_t left_start      = start;
        size_t left_end        = mid;
        size_t left_sub_start  = left_start;
        size_t left_sub_end    = left_end;
        size_t right_start     = mid + 1;
        size_t right_end       = end;
        size_t right_sub_start = right_start;
        size_t right_sub_end   = right_end;
        size_t cross_start     = start;
        size_t cross_end       = end;
        size_t cross_sub_start = cross_start;
        size_t cross_sub_end   = cross_end;
        long int left_sum      = 0;
        long int right_sum     = 0;
        long int cross_sum     = 0;

        left_sum = maximum_subarray (array, left_start, left_end,
                &left_sub_start, &left_sub_end);
        right_sum = maximum_subarray (array, right_start, right_end,
                &right_sub_start, &right_sub_end);
        cross_sum = maximum_crossing_subarray (array, cross_start,
                mid, cross_end, &cross_sub_start, &cross_sub_end);

        if (left_sum >= right_sum && left_sum >= cross_sum) {
            *sub_start = left_sub_start;
            *sub_end = left_sub_end;
            return left_sum;

        } else if (right_sum >= left_sum && right_sum >= cross_sum) {
            *sub_start = right_sub_start;
            *sub_end = right_sub_end;
            return right_sum;

        } else {
            *sub_start = cross_sub_start;
            *sub_end = cross_sub_end;
            return cross_sum;

        }

        printf("Exiting maximum_subarray\n");

    }

}

/* -------------------------------------------------------------------------- *
 * Function 'maximum_crossing_subarray'
 * --------------------------------------------------------------------------
 * 
 * This function implements the maximum crossing subarray algorithm. It is a
 * helper function for the maximum subarray algorithm.
 * 
 * Parameters:
 *    array: Pointer to the array of long integers.
 *    start: Index of the first element of the array to start searching
 *    subarray for.
 *    mid: Index of the middle element of the array.
 *    end: Index of the last element of the array to end searching
 *    subarray for.
 *    left: Pointer to the index of the first element of the
 *    maximum subarray.
 *    right: Pointer to the index of the last element of the
 *    maximum subarray.
 * 
 * Returns:
 *    The sum of the maximum subarray.
 * 
 * Notes:
 *    The function assumes that the array has at least one element.
 * 
 * Example:
 *    long int array[] = { 1, 2, 3, 4, 5 };
 *    size_t start = 0;
 *    size_t mid = 2;
 *    size_t end = 4;
 *    size_t left;
 *    size_t right;
 *    long int sum = maximum_crossing_subarray (array, start, mid, end,
 *        &left, &right); 
 * 
 * -------------------------------------------------------------------------- */
long int maximum_crossing_subarray (const long int *array,
        const size_t start, const size_t mid, const size_t end, size_t *left, size_t *right) {
    long int left_sum = 0;
    long int sum = 0;
    for (size_t i = mid; i + 1 > start; i--) {
        sum += *(array + i);
        if (sum > left_sum) {
            left_sum = sum;
            *left = i;

        }

    }

    long int right_sum = 0;
    sum = 0;
    for (size_t i = mid + 1; i <= end; i++) {
        sum += *(array + i);
        if (sum > right_sum) {
            right_sum = sum;
            *right = i;

        }

    }

    return left_sum + right_sum;

}