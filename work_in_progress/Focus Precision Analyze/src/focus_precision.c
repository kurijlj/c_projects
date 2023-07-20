/* ==========================================================================
 *  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of Focus Precision Analyze.
 *
 * Focus Precision Analyze is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Focus Precision Analyze is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with Focus Precision Analyze. If not, see <https://www.gnu.org/licenses/>.
 * ========================================================================== */


/* ==========================================================================
 *
 * 2023-07-20 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * focus_precision.c: created.
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
#include <gtk/gtk.h>


/* ==========================================================================
 * Macros definitions section
 * ========================================================================== */

#define APP_NAME             "focus_precision"
#define APP_VERSION          "0.1"
#define APP_IDENTIFIER       "Focus.Precision.Analyze"
#define APP_AUTHOR           "Ljubomir Kurij"
#define APP_EMAIL            "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR   "2023"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE          "GPLv3+"
#define APP_LICENSE_URL      "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION      "Focus Precision Measurement Log Viewer"
#ifdef _WIN32
#define APP_USAGE_A          "app_name.exe [OPTION]..."
#else
#define APP_USAGE_A          "app_name [OPTION]..."
#endif  /* End of platform specific macro definition */
#define APP_EPILOGUE         "\nReport bugs to <" APP_EMAIL ">."


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

int short_usage(
        struct argparse *self,
        const struct argparse_option *option
        );
int version_info(
        struct argparse *self,
        const struct argparse_option *option
        );


/* ==========================================================================
 * GTK 4 connect activate signal to a callback function
 * ========================================================================== */

static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Focus Precision Analyze");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

    gtk_window_set_child (GTK_WINDOW (window), box);

    button = gtk_button_new_with_label ("Hello \"Focus\"!");

    g_signal_connect_swapped (button, "clicked",
            G_CALLBACK (gtk_window_destroy), window);

    gtk_box_append (GTK_BOX (box), button);

    gtk_widget_show (window);

}


/* ==========================================================================
 * Main module
 * ========================================================================== */

int main(int argc, char **argv) {

    int usage = 0;
    int version = 0;

    /* Define command line options */
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

    /* Parse command line arguments */
    struct argparse argparse;
    argparse_init(&argparse, options, kUsages, 0);
    argparse_describe(&argparse, APP_DESCRIPTION, APP_EPILOGUE);
    argc = argparse_parse(&argparse, argc, argv);

    /* Check if usage or version options were given */
    if (usage != 0 || version != 0) {
        exit(EXIT_SUCCESS);

    }

    /* Main module code */
    int status = EXIT_SUCCESS;

    if (argc == 0) {
        /* No arguments were given */

        /* Let's build a simple GTK v4 application */
        GtkApplication *app;

        app = gtk_application_new (APP_IDENTIFIER, G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);

    }

    return status;

}


/* ==========================================================================
 * Utility function definitions
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: short_usage(
 *              struct argparse *self,
 *              const struct argparse_option *option
 *              )
 * --------------------------------------------------------------------------
 * 
 * Description: Print a short usage message
 * 
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure 
 * 
 * Returns: Number of characters printed
 * 
 * -------------------------------------------------------------------------- */
int short_usage(struct argparse *self, const struct argparse_option *option) {
    #ifdef _WIN32
    return fprintf(stdout, "%s %s\n%s%s%s\n", 
        "Usage:", APP_USAGE_A,
        "Try `", APP_NAME, ".exe -h' for more information."
        );
    #else
    return fprintf(stdout, "%s %s\n%s%s%s\n", 
        "Usage:", APP_USAGE_A,
        "Try `", APP_NAME, " -h' for more information."
        );
    #endif  /* End of platform specific code */

}

/* --------------------------------------------------------------------------
 * Function: version_info(
 *              struct argparse *self,
 *              const struct argparse_option *option
 *              )
 * --------------------------------------------------------------------------
 * 
 * Description: Print program version information
 * 
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure 
 * 
 * Returns: Number of characters printed
 * 
 * -------------------------------------------------------------------------- */
int version_info(struct argparse *self, const struct argparse_option *option) {
    return fprintf(stdout, "%s %s %s %s %s\n%s %s: %s <%s>\n%s\n%s\n",
            APP_NAME, APP_VERSION, "Copyright (c)",
            APP_COPYRIGHT_YEAR, APP_AUTHOR,
            "License", APP_LICENSE, "GNU GPL version 3 or later",
            APP_LICENSE_URL,
            "This is free software: you are free "
            "to change and redistribute it.",
            "There is NO WARRANTY, to the extent permitted by law."
            );

}
