/* ==========================================================================
 *  linked_list - Implementation of the linked list data structure.
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
 * * linked_list.c: created.
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
#include <time.h>

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
 * Linked list implementation declarations
 * ========================================================================== */
typedef enum list_data_type {
    char_type,
    unsigned_char_type,
    short_type,
    unsigned_short_type,
    int_type,
    unsigned_int_type,
    long_type,
    unsigned_long_type,
    long_long_type,
    unsigned_long_long_type,
    float_type,
    double_type,
    long_double_type,
    pointer_type,
    string_type
} list_data_type_t;

typedef struct list_node {
    void *data;
    struct list_node *next;
} list_node_t;

typedef struct list {
    list_node_t *head;
    list_node_t *tail;
    size_t size;
} list_t;

void         list_node_init (list_node_t * const node, const void * const data);
void         list_init (list_t * const list);
void         list_destroy (list_t * const list);
int          list_push_front (list_t * const list, void * const data);
void        *list_get_front (const list_t * const list);
void        *list_pop_front (list_t * const list);
int          list_push_back (list_t * const list, void * const data);
void        *list_get_back (const list_t * const list);
void        *list_pop_back (list_t * const list);
int          list_is_empty (const list_t * const list);
size_t       list_size (const list_t * const list);
list_node_t *list_find (const list_t * const list, const void * const data);
void         list_node_print (const list_node_t * const node,
        const list_data_type_t type);
void         list_print (const list_t *list, const list_data_type_t data_type);


/* ==========================================================================
 * Main module
 * ========================================================================== */

int main (int argc, const char **argv) {

    int usage   = 0;
    int number  = 20;
    int version = 0;

    struct argparse_option options[] = {
        OPT_GROUP ("General options"),
        OPT_HELP (),
        OPT_BOOLEAN ('\0', "usage", &usage, "give a short usage message",
            &short_usage, 0, 0),
        OPT_BOOLEAN ('V', "version", &version, "print program version",
            &version_info, 0, 0),
        OPT_GROUP ("Array options"),
        OPT_INTEGER ('s', "array-size", &number,
            "defines number of elements in a array/list", NULL, 0, 0),
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
        printf ("\n");

        /* Initialize random number generator */
        srand (time(NULL));

        /* Initialize the array */
        int *array = malloc (number * sizeof(int));
        if (array == NULL) {
            fprintf (stderr, "%s: malloc: Error allocating memory for array\n",
                kAppName);
            exit (EXIT_FAILURE);

        }

        /* Fill the array with random numbers */
        for (size_t i = 0; i < (size_t) number; i++) {
            array[i] = rand() % 100;

        }

        /* Construct a linked list from the array */
        list_t list;
        list_init (&list);
        for (size_t i = 0; i < (size_t) number; i++) {
            list_push_back (&list, &array[i]);

        }

        printf ("\n");

        /* Print the array content */
        printf ("Array content:\n");
        for (size_t i = 0; i < (size_t) number; i++) {
            printf ("item(%lu, at: %p, data: %d)\n", (unsigned long) i,
                &array[i], array[i]);

        }
        printf ("\n");

        /* Print the list content */
        printf ("List content:\n");
        list_print (&list, int_type);

        /* Release allocated memory */
        list_destroy (&list);
        free (array);

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
 * linked list implementation definitions
 * ========================================================================== */
void list_node_init (list_node_t * const node, void * const data) {
    node->data = data;
    node->next = NULL;

}

void list_init (list_t * const list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

}

void list_destroy (list_t * const list) {
    /* Remove all nodes from the list */
    while (list->head != NULL) {
        list_pop_front (list);

    }

}

int list_push_front (list_t * const list, void * const data) {
    /* Create a new node */
    list_node_t *node = (list_node_t *) malloc(sizeof(list_node_t));
    if(NULL == node) {
        fprintf(stderr, "%s: malloc: Error allocating memory for node\n",
            kAppName);

        return EXIT_FAILURE;

    }

    /* Initialize the node */
    list_node_init(node, data);

    /* Debug output */
    printf("%s: list_push_front: ", kAppName);
    list_node_print(node, int_type);

    /* Add the node to the front of the list */
    node->next = list->head;
    list->head = node;

    /* Update the tail if the list was empty */
    if (list->tail == NULL) {
        list->tail = node;

    }

    /* Update the size of the list */
    list->size++;

    return EXIT_SUCCESS;

}

void *list_get_front (const list_t * const list) {
    /* Return the data stored in the first node */
    return list->head->data;

}

void *list_pop_front (list_t * const list) {
    /* Get the data stored in the first node */
    void *data = list->head->data;

    /* Remove the first node */
    list_node_t *node = list->head;
    list->head = list->head->next;
    node->next = NULL;

    /* Debug output */
    printf("%s: list_push_front: ", kAppName);
    list_node_print(node, int_type);

    free(node);

    /* Update the tail if the list is now empty */
    if (list->head == NULL) {
        list->tail = NULL;

    }

    /* Update the size of the list */
    list->size--;

    return data;

}

int list_push_back (list_t * const list, void * const data) {
    /* Create a new node */
    list_node_t *node = (list_node_t *) malloc(sizeof(list_node_t));
    if(NULL == node) {
        fprintf(stderr, "%s: calloc: Error allocating memory for node\n",
            kAppName);

        return EXIT_FAILURE;

    }

    /* Initialize the node */
    list_node_init(node, data);

    /* Debug output */
    printf("%s: list_push_front: ", kAppName);
    list_node_print(node, int_type);

    /* Add the node to the back of the list */
    if (list->tail != NULL) {
        list->tail->next = node;

    }

    list->tail = node;

    /* Update the head if the list was empty */
    if (list->head == NULL) {
        list->head = node;

    }

    /* Update the size of the list */
    list->size++;

    return EXIT_SUCCESS;

}

void *list_get_back (const list_t * const list) {
    /* Return the data stored in the last node */
    return list->tail->data;

}

void *list_pop_back (list_t * const list) {
    /* Get the data stored in the last node */
    void *data = list->tail->data;

    /* Remove the last node */
    list_node_t *node = list->head;
    while (node->next != list->tail) {
        node = node->next;

    }

    node->next = NULL;

    /* Debug output */
    printf("%s: list_push_front: ", kAppName);
    list_node_print(list->tail, int_type);

    free(list->tail);
    list->tail = node;

    /* Update the head if the list is now empty */
    if (list->tail == NULL) {
        list->head = NULL;

    }

    /* Update the size of the list */
    list->size--;

    return data;

}

int list_is_empty (const list_t * const list) {
    /* Return true if the list is empty */
    int result = 0;
    if (list->size == 0) {
        result = 1;

    }

    return result;

}

size_t list_size (const list_t * const list) {
    /* Return the size of the list */
    return list->size;

}

list_node_t *list_find (const list_t * const list,
        const void * const data) {
    /* Check if the list contains the data */
    list_node_t *node = list->head;
    while (node != NULL) {
        if (node->data == data) {
            return node;

        }

        node = node->next;

    }

    return NULL;

}

void list_node_print (const list_node_t * const node,
        const list_data_type_t data_type) {
    /* Print the data pointed by the data pointer */
    switch (data_type) {
        case char_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf ("%c", *(char *) node->data);
            printf (")\n");
            break;

        case unsigned_char_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%c", *(unsigned char *) node->data);
            printf(")\n");
            break;

        case short_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%d", *(short *) node->data);
            printf(")\n");
            break;

        case unsigned_short_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%d", *(unsigned short *) node->data);
            printf(")\n");
            break;

        case int_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%d", *(int *) node->data);
            printf(")\n");
            break;

        case unsigned_int_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%d", *(unsigned int *) node->data);
            printf(")\n");
            break;

        case long_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%ld", *(long *) node->data);
            printf(")\n");
            break;

        case unsigned_long_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%ld", *(unsigned long *) node->data);
            printf(")\n");
            break;

        case float_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%f", *(float *) node->data);
            printf(")\n");
            break;

        case double_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%f", *(double *) node->data);
            printf(")\n");
            break;

        case long_double_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%Lf", *(long double *) node->data);
            printf(")\n");
            break;

        case pointer_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%p", *(void **) node->data);
            printf(")\n");
            break;

        case string_type:
            printf ("list_node_t(at: %p, ", node);
            printf ("data at: %p, ", node->data);
            printf("%s", (char *) node->data);
            printf(")\n");
            break;

        default:
            fprintf(stderr, "%s: list_node_print: Invalid data type\n",
                    kAppName);
            break;

    }

}
void list_print (const list_t * const list, const list_data_type_t data_type) {
    /* Print the list */
    list_node_t *node = list->head;
    while (node != NULL) {
        /* Print data pointed by the data pointer */
        list_node_print(node, data_type);

        node = node->next;

    }

    printf("\n");

}