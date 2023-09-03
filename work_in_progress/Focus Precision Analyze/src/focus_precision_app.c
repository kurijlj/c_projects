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
 * 2023-07-22 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * focus_precision_app.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */
#include "focus_precision_app.h"
#include "main_app_window.h"

/* External libraries headers */
#include <gtk/gtk.h>


/* ==========================================================================
 * FocusPrecisionApp class definition section
 * ========================================================================== */

/* -------------------------------------------------------------------------- *
 * FocusPrecisionApp class definition
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     FocusPrecisonApp class definition.
 * 
 * Fields:
 *    parent: GtkApplication  Parent class.
 * 
 * -------------------------------------------------------------------------- */
struct _FocusPrecisionApp {
    GtkApplication parent;

};

/* Use macro to define FocusPrecisionApp class type */
G_DEFINE_TYPE(FocusPrecisionApp, focus_precision_app, GTK_TYPE_APPLICATION);


/* ==========================================================================
 * FocusPrecisionApp class implementation section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: focus_precision_app_init(FocusPrecisionApp *app)
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     Initialize FocusPrecisionApp class
 * 
 * Parameters:
 *     app : Pointer to FocusPrecisionApp class
 * 
 * Returns:
 *     Nothing
 * 
 * -------------------------------------------------------------------------- */
static void focus_precision_app_init (FocusPrecisionApp *app) {
    /* No initialization needed */

}

/* --------------------------------------------------------------------------
 * Function: focus_precision_app_activate(FocusPrecisionApp *app)
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     Handle 'activate' signal by creating a new main window.
 * 
 * Parameters:
 *     app : Pointer to FocusPrecisionApp class
 * 
 * Returns:
 *     Nothing
 * 
 * -------------------------------------------------------------------------- */
static void focus_precision_app_activate (GApplication *app) {
    MainAppWindow *win;

    /* Create a new main window */
    win = main_app_window_new (FOCUS_PRECISION_APP (app));

    /* Present the main window */
    gtk_window_present (GTK_WINDOW (win));

}

/* --------------------------------------------------------------------------
 * Function: focus_precision_app_class_init(FocusPrecisionAppClass *class)
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     Initialize FocusPrecisionAppClass class. Mostly used to connect signals
 *    to their handlers.
 * 
 * Parameters:
 *     class : Pointer to FocusPrecisionAppClass class
 * 
 * Returns:
 *     Nothing
 * 
 * -------------------------------------------------------------------------- */
static void focus_precision_app_class_init (FocusPrecisionAppClass *class) {
    G_APPLICATION_CLASS (class)->activate = focus_precision_app_activate;

}

/* --------------------------------------------------------------------------
 * Function: focus_precision_app_new(const GChar *app_id)
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     Create a new FocusPrecisionApp class instance.
 * 
 * Parameters:
 *     app_id : Application ID
 * 
 * Returns:
 *     Pointer to FocusPrecisionApp instance
 * 
 * -------------------------------------------------------------------------- */
FocusPrecisionApp *focus_precision_app_new (const char *app_id) {
    return g_object_new (FOCUS_PRECISION_APP_TYPE, "application-id", app_id,
            "flags", G_APPLICATION_DEFAULT_FLAGS, NULL);

}