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


#ifndef __CORE_H__
#define __CORE_H__


#include <sys/stat.h>
#include <glib.h>

typedef struct
{
  gchar *fname;
  struct stat flstat;
  guint timeout;
} fatrib;


fatrib *
  validate_file						(gchar *fname);

gchar *
  check_file						(fatrib *pfatrib);

gchar *
  strip_path						(gchar *path);


gint 
  monitor_file_timeout				(gpointer note_child);
#endif
