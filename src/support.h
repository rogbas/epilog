/* 
   Copyright (C) 2002 Rog�rio Bastos. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  

*/

#include <gnome.h>


GtkWidget*  lookup_widget              (GtkWidget       *widget,
                                        const gchar     *widget_name);

#define get_widget lookup_widget



GtkWidget*  create_pixmap              (GtkWidget       *widget,
                                        const gchar     *filename,
                                        gboolean         gnome_pixmap);

GdkImlibImage* create_image            (const gchar     *filename);

