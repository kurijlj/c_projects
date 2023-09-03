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
 * * main_window.h: created.
 *
 * ========================================================================== */


#ifndef __MAIN_APP_WINDOW_H
#define __MAIN_APP_WINDOW_H

/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */
#include "focus_precision_app.h"

/* External libraries headers */
#include <gtk/gtk.h>


#define MAIN_APP_WINDOW_TYPE (main_app_window_get_type ())
G_DECLARE_FINAL_TYPE (MainAppWindow, main_app_window, MAIN, APP_WINDOW,\
        GtkApplicationWindow)

MainAppWindow *main_app_window_new (FocusPrecisionApp *app);

#endif  /* __MAIN_APP_WINDOW_H */