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
#include <unistd.h>
#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
  GtkWidget *main_window;
  //GtkWidget *add_file_dialog;
  //GtkWidget *fselection;

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif

  gnome_init ("logmonitor", VERSION, argc, argv);

  main_window = create_main_window ();
  //gtk_widget_show (add_file_dialog);
  //add_file_dialog = create_add_file_dialog (main_window);
  
  gtk_widget_show (main_window);

  gtk_main ();
  return 0;
}

