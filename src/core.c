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

#include <sys/stat.h>
#include <glib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "core.h"


fatrib *
  validate_file 					(gchar *fname)
{
  gchar *fname2;
  fatrib *file_stat;
  if (fname == NULL)
    return (NULL);

  file_stat = g_malloc (sizeof (fatrib));
  fname2 = g_strdup (fname);
  file_stat->fname = fname2;
  stat (fname, &file_stat->flstat); 
  //g_free (fname);
  return (file_stat); 
}

gchar *
  check_file						(fatrib *pfatrib)
{
  gchar *buff_diff;
  FILE *fd;
  //gulong old_size;
  glong offset, buff_size;
  struct stat new_stat;
  stat (pfatrib->fname, &new_stat);
  offset = new_stat.st_size - pfatrib->flstat.st_size;
  g_print ("Offset = %lu\n", offset);
  if (offset ==0)
    return (NULL);
  g_print ("Ni!! %u", sizeof (gchar)); 
  buff_size = (offset + 1) * sizeof (gchar);
  buff_diff = g_malloc (buff_size);
  memset (buff_diff, 0, buff_size); 
  if ((fd = fopen (pfatrib->fname, "r")) == NULL)
    return (NULL);
  fseek (fd, pfatrib->flstat.st_size, SEEK_SET);
  fread (buff_diff, offset, 1, fd);
  pfatrib->flstat = new_stat;
  return (buff_diff);
}

gint 
  monitor_file_timeout				(gpointer note_child)
{
  GdkColor vermelho;
  GtkRcStyle *rc_red;
  GtkWidget *log_screen;
  GtkWidget *notebook, *ast_label;
  fatrib *pfatrib;
  gchar *diff_text;
  gint pos; 
  pfatrib = gtk_object_get_data (GTK_OBJECT(note_child), "file_stat");
  log_screen = gtk_object_get_data (GTK_OBJECT(note_child), "log_screen");
  diff_text = check_file (pfatrib);
  if (diff_text == NULL)
    return (TRUE);
  notebook = gtk_object_get_data (GTK_OBJECT(note_child), "notebook");

  if (gtk_notebook_get_current_page (GTK_NOTEBOOK(notebook)) != gtk_notebook_page_num (GTK_NOTEBOOK(notebook), GTK_WIDGET(note_child)))
  {
    vermelho.red = 65535;
    vermelho.blue = 0;
    vermelho.green = 0;

    gdk_color_parse ("red", &vermelho);

    rc_red = gtk_rc_style_new ();
    rc_red->fg[GTK_STATE_NORMAL] = vermelho;
    rc_red->color_flags[GTK_STATE_NORMAL] |= GTK_RC_FG;
  
    ast_label = gtk_notebook_get_tab_label (GTK_NOTEBOOK(notebook), GTK_WIDGET(note_child));
    gtk_widget_modify_style (ast_label, rc_red);
    gtk_rc_style_unref (rc_red);
  }
  //pos = gtk_editable_get_position (GTK_EDITABLE(log_screen));
  //txt = strip_path (pfatrib->fname);
  //ast_text = g_strconcat ("*", txt);
  //txt = g_strdup (strip_path (pfatrib->fname));
  //ast_text = g_strconcat ("*", txt);
  //ast_label = gtk_label_new (ast_text);
  g_print ("\nFname: %s\n", pfatrib->fname);
  //g_print ("\nLabel: %s\n", ast_text);
  //gtk_notebook_set_tab_label (GTK_NOTEBOOK(notebook), GTK_WIDGET(note_child), GTK_WIDGET(ast_label));
  pos = gtk_text_get_length (GTK_TEXT(log_screen));
  gtk_editable_insert_text (GTK_EDITABLE(log_screen), diff_text, strlen (diff_text), &pos);
  //g_free (ast_text);
  g_free (diff_text);
  return (TRUE);
}

gchar *
  strip_path									(gchar *path)
{
  gchar *pch;
  
  if (path == NULL)
    return (NULL);
  pch = path;
  while (*pch)
    pch++;

  while (*pch != '/')
    pch--;
  
  pch++;
  return (pch);
}
