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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "core.h"

gboolean
on_main_window_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  g_print ("GoodBye...\n");
  gtk_main_quit ();
  return(FALSE);
}


void
on_add_log_file_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  /*
  gchar *win_title;
  g_assert (user_data != NULL);
  
  win_title = g_strdup (GTK_WINDOW(user_data)->title);
  g_print ("A janela se chama %s\n", win_title);
  g_free (win_title);
  //g_assert (user_data != NULL);
  */
  /*
  GtkWidget *afd;
  g_assert (user_data != NULL);
  afd = gtk_object_get_data (GTK_OBJECT(user_data), "add_file_dialog");
  gtk_widget_show (afd);
  */

  GtkWidget *fselector;
  fselector = create_fselector (GTK_WIDGET(user_data));
  gtk_widget_show (fselector);
  
  }


void
on_remove_log_file_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  g_assert (user_data != NULL);
}


void
on_exit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  g_print ("GoodBye...\n");
  gtk_main_quit ();
}


void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *about;
  const gchar *authors[] = {
		  "Rogério Villela de Lima Bastos \"Epic\" (rogbas@terra.com.br)", NULL };
  about = gnome_about_new ("Epilog", VERSION, "Copyright 2002 Rogério Bastos.", (const gchar **) authors, "Multi-file logging program with key word coloring", NULL);
  gtk_widget_show (about);

 
}


gboolean
on_add_file_window_delete_event        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{

  return FALSE;
}

/*
void
  on_browse_button						(GtkWidget		*widget,
										 GdkEvent		*event,
										 gpointer		user_data)
*/
void
  on_browse_button						(GtkObject *obj)
{
  /*
  GtkWidget *fselector, *main_window;
  gchar *title;
  g_assert (user_data != NULL);
  //title = g_strdup (GTK_WINDOW(user_data)->title);
  //main_window = gtk_object_get_data ( GTK_OBJECT(user_data), "main_window");
  //g_assert (main_window != NULL);
  fselector = gtk_object_get_data (GTK_OBJECT(user_data), "fselector"); 
  g_assert (fselector != NULL);
  gtk_widget_show (fselector);
  //g_print ("Title: %s", title);
  //g_free (title);
  */
  GtkWidget *fselector;
  fselector = gtk_object_get_data (GTK_OBJECT(obj), "fselector");
  g_assert (fselector != NULL);
  gtk_widget_show (fselector);
}


void
on_add_file_close						(GtkWidget		*widget,
										 GdkEvent		*event,
										 gpointer		user_data)
{
  gtk_widget_hide (widget);
}

GtkWidget *
  create_note_child						(fatrib *pfatrib)
{
  GtkWidget *note_child, *sw, *log_screen,
  			*hbox1, *check_color, *check_ascroll;

  note_child = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (note_child);

  sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (sw);
  gtk_box_pack_start (GTK_BOX (note_child), sw, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  log_screen = gtk_text_new (NULL, NULL);
  gtk_object_set_data (GTK_OBJECT(note_child), "log_screen", log_screen);
  gtk_widget_show (log_screen);
  gtk_container_add (GTK_CONTAINER (sw), log_screen);

  hbox1 = gtk_hbox_new (TRUE, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (note_child), hbox1, FALSE, TRUE, 0);

  check_color = gtk_check_button_new_with_label (_("Color"));
  gtk_widget_show (check_color);
  gtk_box_pack_start (GTK_BOX (hbox1), check_color, FALSE, FALSE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_color), TRUE);

  check_ascroll = gtk_check_button_new_with_label (_("Auto Scroll"));
  gtk_widget_show (check_ascroll);
  gtk_box_pack_start (GTK_BOX (hbox1), check_ascroll, FALSE, FALSE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_ascroll), TRUE);
  
  gtk_object_set_data (GTK_OBJECT(note_child), "file_stat", pfatrib);

  return (note_child);
}
void
select_file								(GtkObject *main_window)
{
  GtkWidget *fselector;
  GtkWidget *notebook, *note_child, *note_label;
  gchar *sel_file;
  fatrib *pfatrib;
  //gint *num_files; 
  fselector = gtk_object_get_data (GTK_OBJECT(main_window), "fselector");
  //fselector = GTK_WIDGET(main_window);
  sel_file = gtk_file_selection_get_filename (GTK_FILE_SELECTION(fselector));

  pfatrib = validate_file (sel_file);
  if (pfatrib == NULL)
  {
    g_print ("Arquivo invalido\n");
    return;
  }
  
  notebook = gtk_object_get_data (GTK_OBJECT(main_window), "note_file");
  //num_files = gtk_object_get_data (GTK_OBJECT(main_window), "num_files");
  //(*num_files)++;
  //gtk_object_set_data (GTK_OBJECT(main_window), "num_files", &num_files);
  note_child = create_note_child (pfatrib);
  gtk_object_set_data (GTK_OBJECT(note_child), "notebook", notebook);
  note_label = gtk_label_new (strip_path (sel_file));
  
  gtk_notebook_append_page (GTK_NOTEBOOK(notebook), note_child, note_label);
  
  pfatrib->timeout = gtk_timeout_add (3000, monitor_file_timeout, note_child);

  g_free (sel_file);

}


void
hide_obj								(GtkWidget *widget)
{
	gtk_widget_hide (GTK_WIDGET(widget));
}

void
  destroy_widget						(GtkWidget *window)
{
  GtkWidget *fselector;
  fselector = gtk_object_get_data (GTK_OBJECT(window), "fselector");
  gtk_object_remove_data (GTK_OBJECT(window), "fselector");
  gtk_widget_hide (GTK_WIDGET(fselector));
}

void
  unbold_tab						(GtkNotebook		*notebook,
				  					 GtkNotebookPage 	*note_page,
									 gint				page,
									 gpointer			user_data)
{
  GtkWidget *label;
  GdkColor preto;
  GtkRcStyle *rc_bk;
  preto.red = 0;
  preto.blue = 0;
  preto.green = 0;
  gdk_color_parse ("black", &preto);
  
  rc_bk = gtk_rc_style_new ();
  rc_bk->fg[GTK_STATE_NORMAL] = preto;
  rc_bk->color_flags[GTK_STATE_NORMAL] |= GTK_RC_FG;
  
  label = GTK_WIDGET(note_page->tab_label);
  gtk_widget_modify_style (label, rc_bk);
  gtk_rc_style_unref (rc_bk);
}
