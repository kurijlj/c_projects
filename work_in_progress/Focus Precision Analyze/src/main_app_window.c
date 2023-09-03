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
 * * main_window.c: created.
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
 * MainAppWindow class definition section
 * ========================================================================== */

/* -------------------------------------------------------------------------- *
 * MainAppWindow class definition
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     MainAppWindow class definition.
 * 
 * Fields:
 *    parent: GtkApplicationWindow  Parent class.
 * 
 * -------------------------------------------------------------------------- */
struct _MainAppWindow {
    GtkApplicationWindow parent;

};


/* ==========================================================================
 * MainAppWindow class implementation section
 * ========================================================================== */


/* Use macro to define MainAppWindow class type */
G_DEFINE_TYPE(MainAppWindow, main_app_window,\
        GTK_TYPE_APPLICATION_WINDOW);


/* -------------------------------------------------------------------------- *
 * Function: main_app_window_init(MainAppWindow *app)
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     Initialize MainAppWindow class.
 * 
 * Parameters:
 *    app : Pointer to MainAppWindow class
 * 
 * Returns:
 *    Nothing
 * 
 * -------------------------------------------------------------------------- */
static void main_app_window_init (MainAppWindow *win) {
    /* Initialize MainAppWindow class from template */
    gtk_widget_init_template (GTK_WIDGET (win));

}

/* -------------------------------------------------------------------------- *
 * Function: main_app_window_class_init(MainAppWindowClass *class)
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     Initialize MainAppWindowClass class.
 * 
 * Parameters:
 *    class : Pointer to MainAppWindowClass class
 * 
 * Returns:
 *    Nothing
 * 
 * -------------------------------------------------------------------------- */
static void main_app_window_class_init (MainAppWindowClass *class) {
    /* Set template from resource */
    gtk_widget_class_set_template_from_resource (
        GTK_WIDGET_CLASS (class),
        "/c_projects/focus_precision_app/main_app_window.ui"
        );


}

/* -------------------------------------------------------------------------- *
 * Function: main_app_window_new(FocusPrecisionApp *app)
 * --------------------------------------------------------------------------
 * 
 * Description:
 *     Create new MainAppWindow class instance.
 * 
 * Parameters:
 *    app : Pointer to FocusPrecisionApp instance
 * 
 * Returns:
 *    Pointer to MainAppWindow instance
 * 
 * -------------------------------------------------------------------------- */
MainAppWindow *main_app_window_new (FocusPrecisionApp *app) {
    /* Create new MainAppWindow instance and set application attribute to
       point to instance of FocusPrecisionApp class.
     */
    return g_object_new (MAIN_APP_WINDOW_TYPE, "application", app, NULL);

}