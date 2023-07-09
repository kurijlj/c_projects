/* ==========================================================================
 *  tree_implementation - Implementation of the tree abstract data type.
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
 * 2023-07-07 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * tree_implementation.c: created.
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

static const char *const kAppName = "inplace_insertion_sort";
static const char *const kDescription = "\n"
    "Implementation of in-place insertion sort algorithm.\n\n"
    "Mandatory arguments to long options are mandatory for short options too.";
static const char *const kEpilogue = "\nReport bugs to <author@email.com>.";
static const char *const kUsages[] = {
    "inplace_insertion_sort [OPTION]...",
    "inplace_insertion_sort ...",
    NULL,
};


/* ==========================================================================
 * Utility function declarations
 * ========================================================================== */

void short_usage (struct argparse *self,
        const struct argparse_option *option);
void version_info (struct argparse *self,
        const struct argparse_option *option);


/* ========================================================================== *
 * Tree implementation declarations
 * ========================================================================== */
typedef struct tree_node {
    void *data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct tree {
    tree_node_t *root;
} tree_t;

int tree_node_init(tree_node_t *node, void *data);
void tree_node_destroy(tree_node_t *node);
void tree_init(tree_t *tree);
void tree_destroy(tree_t *tree);
void tree_insert(tree_t *tree, void *data);
void tree_remove(tree_t *tree, void *data);
void tree_print(tree_t *tree);
void tree_print_node(tree_node_t *node);
void tree_print_node_data(tree_node_t *node, void (*print)(void *data));


/* ==========================================================================
 * Main module
 * ========================================================================== */

int main (int argc, const char **argv) {

    int usage   = 0;
    int version = 0;

    struct argparse_option options[] = {
        OPT_GROUP ("General options"),
        OPT_HELP (),
        OPT_BOOLEAN ('\0', "usage", &usage, "give a short usage message",
            &short_usage, 0, 0),
        OPT_BOOLEAN ('V', "version", &version, "print program version",
            &version_info, 0, 0),
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
        printf ("%s Main module running ...\n", kAppName);

    }

    return EXIT_SUCCESS;

}


/* ========================================================================== *
 * Utility function definitions
 * ========================================================================== */

void short_usage (struct argparse *self,
        const struct argparse_option *option) {
    fprintf (stdout, "Usage: inplace_insertion_sort  [OPTION]...\n"
        "Try `inplace_insertion_sort  -h' for more information.\n"
        );

}

void version_info (struct argparse *self,
        const struct argparse_option *option) {
    fprintf (stdout, "inplace_insertion_sort 0.1 Copyright (C) 2023 "
        "Author Name\n"
        "License GPLv3+: GNU GPL version 3 or later "
        "<http://gnu.org/licenses/gpl.html>\n"
        "This is free software: you are free to change and redistribute it.\n"
        "There is NO WARRANTY, to the extent permitted by law.\n"
        );

}


/* ========================================================================== *
 * Tree implementation definitions
 * ========================================================================== */
int tree_node_init(tree_node_t *node, void *data) {
    node = (tree_node_t*) malloc(sizeof(tree_node_t));

    /* Check if memory allocation was successful */
    if (node == NULL) {
        fprintf(stderr,
            "%s: Error: tree_node_init: memory allocation failed.\n",
            kAppName);

        return EXIT_FAILURE;

    }

    /* Initialize node */
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return EXIT_SUCCESS;

}

void tree_node_destroy(tree_node_t *node) {
    /* Check if node is NULL */
    if (node == NULL) {
        fprintf(stderr,
            "%s: Error: tree_node_destroy: node is NULL.\n",
            kAppName);

        return;

    }

    /* Check if node has children */
    if (node->left != NULL) {
        tree_node_destroy(node->left);

    }

    if (node->right != NULL) {
        tree_node_destroy(node->right);

    }

    /* Free node */
    free(node);

}

void tree_init(tree_t *tree) {
    tree = (tree_t*) malloc(sizeof(tree_t));

    /* Check if memory allocation was successful */
    if (tree == NULL) {
        fprintf(stderr,
            "%s: Error: tree_init: memory allocation failed.\n",
            kAppName);

        return;

    }

    /* Initialize tree */
    tree->root = NULL;

}

void tree_destroy(tree_t *tree) {
    /* Check if tree is NULL */
    if (tree == NULL) {
        fprintf(stderr,
            "%s: Error: tree_destroy: tree is NULL.\n",
            kAppName);

        return;

    }

    /* Check if tree has root */
    if (tree->root != NULL) {
        tree_node_destroy(tree->root);

    }

    /* Free tree */
    free(tree);

}

void tree_insert(tree_t *tree, void *data) {
    /* Check if tree is NULL */
    if (tree == NULL) {
        fprintf(stderr,
            "%s: Error: tree_insert: tree is NULL.\n",
            kAppName);

        return;

    }

    /* Check if tree has root */
    if (tree->root == NULL) {
        tree_node_init(tree->root, data);

    } else {
        /* We are keeping the tree balanced by inserting new nodes
         * in a way that the tree is always a complete binary tree.
         * This means that the tree is always filled from left to right
         * on each level. To find first unpopulated node we need to
         * traverse the tree in a breadth-first manner.
         */
    }

}