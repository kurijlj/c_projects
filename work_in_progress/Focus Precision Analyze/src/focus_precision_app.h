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
 * * focus_precision_app.h: created.
 *
 * ========================================================================== */


#ifndef __FOCUS_PRECISION_APP_H
#define __FOCUS_PRECISION_APP_H

/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* External libraries headers */
#include <gtk/gtk.h>


/* See <https://docs.gtk.org/gobject/func.DECLARE_FINAL_TYPE.html> for
 * details on G_DECLARE_FINAL_TYPE macro
 */
#define FOCUS_PRECISION_APP_TYPE (focus_precision_app_get_type ())
G_DECLARE_FINAL_TYPE (FocusPrecisionApp, focus_precision_app, FOCUS_PRECISION,\
        APP, GtkApplication)

FocusPrecisionApp *focus_precision_app_new (const char *app_id);

#endif  /* __FOCUS_PRECISION_APP_H */