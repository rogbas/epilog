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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

  static GnomeUIInfo item1_menu_uiinfo[] =
{
  {
    GNOME_APP_UI_ITEM, N_("Add Log File"),
    NULL,
    (gpointer) on_add_log_file_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_OPEN,
    GDK_L, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("Remove Log File"),
    NULL,
    (gpointer) on_remove_log_file_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_CLOSE,
    GDK_R, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
  GNOMEUIINFO_SEPARATOR,
  GNOMEUIINFO_MENU_EXIT_ITEM (on_exit_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo help1_menu_uiinfo[] =
{
  GNOMEUIINFO_MENU_ABOUT_ITEM (on_about_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo menubar1_uiinfo[] =
{
  GNOMEUIINFO_MENU_FILE_TREE (item1_menu_uiinfo),
  GNOMEUIINFO_MENU_HELP_TREE (help1_menu_uiinfo),
  GNOMEUIINFO_END
};

GtkWidget*
create_main_window ()
{
  GtkWidget *main_window; 
  GtkWidget *vbox1;
  GtkWidget *menubar1;
  GtkWidget *vbox2;
  GtkWidget *note_file;
  GtkWidget *statusbar1;
  GtkTooltips *tooltips;
  gint *num_files;
  
  tooltips = gtk_tooltips_new ();
  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_object_set_data (GTK_OBJECT (main_window), "main_window", main_window); 
  gtk_container_set_border_width (GTK_CONTAINER (main_window), 2);
  gtk_window_set_title (GTK_WINDOW (main_window), _("Epilog"));
  gtk_window_set_default_size (GTK_WINDOW (main_window), 330, 450);

  //g_assert (fselector != NULL);
  //g_assert (add_file_dialog != NULL);
  //gtk_object_set_data (GTK_OBJECT(fselector), "main_window", main_window);
  //gtk_object_set_data (GTK_OBJECT(add_file_dialog), "main_window", main_window);
  //gtk_object_set_data (GTK_OBJECT(main_window), "fselector", fselector);
  //gtk_object_set_data (GTK_OBJECT(main_window), "add_file_dialog", add_file_dialog);
  num_files = g_malloc (sizeof (gint));
  *num_files = 0;
  gtk_object_set_data (GTK_OBJECT(main_window), "num_files", &num_files);
  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "vbox1", vbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (main_window), vbox1);
  
  item1_menu_uiinfo[0].user_data = (gpointer) main_window;
  item1_menu_uiinfo[1].user_data = (gpointer) main_window;
  help1_menu_uiinfo[0].user_data = (gpointer) main_window;
  menubar1 = gtk_menu_bar_new ();
  gtk_widget_ref (menubar1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "menubar1", menubar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (menubar1);
  gtk_box_pack_start (GTK_BOX (vbox1), menubar1, FALSE, FALSE, 0);
  gnome_app_fill_menu (GTK_MENU_SHELL (menubar1), menubar1_uiinfo,
                       NULL, FALSE, 0);

  gtk_widget_ref (menubar1_uiinfo[0].widget);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "item1",
                            menubar1_uiinfo[0].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (item1_menu_uiinfo[0].widget);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "add_log_file",
                            item1_menu_uiinfo[0].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (item1_menu_uiinfo[1].widget);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "remove_log_file",
                            item1_menu_uiinfo[1].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (item1_menu_uiinfo[2].widget);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "separator1",
                            item1_menu_uiinfo[2].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (item1_menu_uiinfo[3].widget);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "exit",
                            item1_menu_uiinfo[3].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (menubar1_uiinfo[1].widget);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "help1",
                            menubar1_uiinfo[1].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (help1_menu_uiinfo[0].widget);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "about",
                            help1_menu_uiinfo[0].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox2);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "vbox2", vbox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox2);
  gtk_box_pack_start (GTK_BOX (vbox1), vbox2, TRUE, TRUE, 0);

  note_file = gtk_notebook_new ();
  gtk_widget_ref (note_file);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "note_file", note_file,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_signal_connect (GTK_OBJECT(note_file), "switch-page", GTK_SIGNAL_FUNC(unbold_tab), NULL);
  
  gtk_widget_show (note_file);
  gtk_box_pack_start (GTK_BOX (vbox2), note_file, TRUE, TRUE, 0);

  /*
  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox3);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "vbox3", vbox3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox3);
  gtk_container_add (GTK_CONTAINER (note_file), vbox3);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_ref (scrolledwindow1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "scrolledwindow1", scrolledwindow1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox3), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  log_screen = gtk_text_new (NULL, NULL);
  gtk_widget_ref (log_screen);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "log_screen", log_screen,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (log_screen);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), log_screen);

  hbox1 = gtk_hbox_new (TRUE, 0);
  gtk_widget_ref (hbox1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "hbox1", hbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox3), hbox1, FALSE, TRUE, 0);

  check_color = gtk_check_button_new_with_label (_("Color"));
  gtk_widget_ref (check_color);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "check_color", check_color,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (check_color);
  gtk_box_pack_start (GTK_BOX (hbox1), check_color, FALSE, FALSE, 0);
  gtk_tooltips_set_tip (tooltips, check_color, _("Activate Log Coloring"), NULL);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_color), TRUE);

  check_ascroll = gtk_check_button_new_with_label (_("Auto Scroll"));
  gtk_widget_ref (check_ascroll);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "check_ascroll", check_ascroll,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (check_ascroll);
  gtk_box_pack_start (GTK_BOX (hbox1), check_ascroll, FALSE, FALSE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_ascroll), TRUE);

  label1 = gtk_label_new (_("(none)"));
  gtk_widget_ref (label1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "label1", label1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label1);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (note_file), gtk_notebook_get_nth_page (GTK_NOTEBOOK (note_file), 0), label1);
  gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label1), TRUE);
  */
  statusbar1 = gtk_statusbar_new ();
  gtk_widget_ref (statusbar1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "statusbar1", statusbar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (statusbar1);
  gtk_box_pack_start (GTK_BOX (vbox2), statusbar1, FALSE, FALSE, 2);

  gtk_signal_connect_object (GTK_OBJECT (main_window), "delete_event",
                             GTK_SIGNAL_FUNC (on_main_window_delete_event),
                             GTK_OBJECT (main_window));

  gtk_object_set_data (GTK_OBJECT (main_window), "tooltips", tooltips);

  return main_window;
}

GtkWidget*
create_add_file_dialog (GtkWidget *main_window)
{
  GtkWidget *add_file_dialog;
  GtkWidget *hbox2;
  GtkWidget *entry_file;
  GtkWidget *but_browse;

  add_file_dialog = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (add_file_dialog), "add_file_dialog", add_file_dialog);
  gtk_container_set_border_width (GTK_CONTAINER (add_file_dialog), 5);
  gtk_window_set_title (GTK_WINDOW (add_file_dialog), _("Add Log File"));
  gtk_window_set_default_size (GTK_WINDOW (add_file_dialog), 330, 50);
  gtk_window_set_policy (GTK_WINDOW (add_file_dialog), TRUE, TRUE, FALSE);
  gtk_signal_connect (GTK_OBJECT(add_file_dialog), "delete_event",
				  GTK_SIGNAL_FUNC(on_add_file_close), NULL);
  gtk_object_set_data (GTK_OBJECT(add_file_dialog), "main_window", main_window);
  gtk_object_set_data (GTK_OBJECT(main_window), "add_file_dialog", add_file_dialog);
  
  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox2);
  gtk_object_set_data_full (GTK_OBJECT (add_file_dialog), "hbox2", hbox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox2);
  gtk_container_add (GTK_CONTAINER (add_file_dialog), hbox2);

  entry_file = gtk_entry_new ();
  gtk_widget_ref (entry_file);
  gtk_object_set_data_full (GTK_OBJECT (add_file_dialog), "entry_file", entry_file,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_file);
  gtk_box_pack_start (GTK_BOX (hbox2), entry_file, TRUE, TRUE, 0);
  gtk_widget_set_usize (entry_file, -2, 25);

  but_browse = gtk_button_new_with_label (_("Browse..."));
  gtk_widget_ref (but_browse);
  gtk_object_set_data_full (GTK_OBJECT (add_file_dialog), "but_browse", but_browse,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_signal_connect_object (GTK_OBJECT(but_browse), "clicked", GTK_SIGNAL_FUNC(on_browse_button), GTK_OBJECT(main_window)); 
  gtk_widget_show (but_browse);
  gtk_box_pack_start (GTK_BOX (hbox2), but_browse, FALSE, FALSE, 0);
  gtk_widget_set_usize (but_browse, 85, 25);
  GTK_WIDGET_UNSET_FLAGS (but_browse, GTK_CAN_FOCUS);
  GTK_WIDGET_SET_FLAGS (but_browse, GTK_CAN_DEFAULT);

  return add_file_dialog;
}

GtkWidget*
create_fselector (GtkWidget *main_window)
{
  GtkWidget *fselector;
  GtkWidget *ok_button1;
  GtkWidget *cancel_button1;

  fselector = gtk_file_selection_new (_("Select Log File"));
  gtk_object_set_data (GTK_OBJECT (fselector), "fselector", fselector);
  gtk_container_set_border_width (GTK_CONTAINER (fselector), 10);
  gtk_object_set_data (GTK_OBJECT(fselector), "main_window", main_window);
  gtk_object_set_data (GTK_OBJECT(main_window), "fselector", fselector);

  gtk_signal_connect_object (GTK_OBJECT(fselector), "delete_event", GTK_SIGNAL_FUNC(destroy_widget), (gpointer) main_window);
  
  ok_button1 = GTK_FILE_SELECTION (fselector)->ok_button;
  gtk_object_set_data (GTK_OBJECT (fselector), "ok_button1", ok_button1);
  gtk_widget_show (ok_button1);
  GTK_WIDGET_UNSET_FLAGS (ok_button1, GTK_CAN_FOCUS);
  GTK_WIDGET_SET_FLAGS (ok_button1, GTK_CAN_DEFAULT);

  gtk_signal_connect_object (GTK_OBJECT(ok_button1), "clicked", GTK_SIGNAL_FUNC(select_file), GTK_OBJECT(main_window));
  
  gtk_signal_connect_object (GTK_OBJECT(ok_button1), "clicked", GTK_SIGNAL_FUNC(destroy_widget), (gpointer) main_window);


  cancel_button1 = GTK_FILE_SELECTION (fselector)->cancel_button;
  gtk_signal_connect_object (GTK_OBJECT(cancel_button1), "clicked", GTK_SIGNAL_FUNC(destroy_widget), (gpointer) main_window);
  gtk_object_set_data (GTK_OBJECT (fselector), "cancel_button1", cancel_button1);
  gtk_widget_show (cancel_button1);
  GTK_WIDGET_SET_FLAGS (cancel_button1, GTK_CAN_DEFAULT);

  return fselector;
}

