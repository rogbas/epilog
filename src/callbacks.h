/* 
   Copyright (C) 2002 Rogério Bastos. All rights reserved.

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


#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#include <gnome.h>
#include "core.h"

gboolean
on_main_window_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_add_log_file_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_remove_log_file_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_exit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_add_file_window_delete_event        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);
/*
void
on_browse_button					   (GtkWidget		*widget,
									    GdkEvent		*event,
										gpointer		user_data);
*/
void
on_browse_button						(GtkObject		*obj);
										
void
on_add_file_close						(GtkWidget		*widget,
										 GdkEvent		*event,
										 gpointer		user_data);


void
select_file								(GtkObject		*main_window);

void
hide_obj								(GtkWidget		*widget);

GtkWidget *
  create_note_child						(fatrib			*pfatrib);
void
  destroy_widget						(GtkWidget		*widget);

void
  unbold_tab						(GtkNotebook		*notebook,
				  					 GtkNotebookPage 	*note_page,
									 gint				page,
									 gpointer			user_data);


#endif
