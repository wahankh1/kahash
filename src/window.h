//	Copyright 2014 Wahankh <dev@wahankh.co.uk>
//	2014-11-22T10:59+00:00

#ifndef WINDOW_H
#define WINDOW_H

#include "core.h"

struct _widgets
{
	GtkWidget *window;
	GtkWidget *toolbar;
	GtkToolItem *toolbar_btn_about;
	GtkToolItem *toolbar_btn_add;
	GtkToolItem *toolbar_btn_preference;
	GtkWidget *notebook;
	GtkWidget *statusbar;
	
	GtkWidget *message_in_view;
	GtkWidget *message_of_input;
	GtkWidget *log_in_view;
	GtkWidget *key_store_view;
	
	GtkWidget *entry_password;
	GtkWidget *entry_name;
	GtkWidget *entry_size;
};

enum { MSG_TIME=0, MSG_TXT, MSG_NUM };
enum { LOG_TXT=0, LOG_NUM };
enum { KEY_ID=0, KEY_NAME, KEY_NUM };

gint kahash_window_build(struct _widgets *widgets);
void kahash_window_toolbar_build(struct _widgets *widgets);
void kahash_window_notebook_build(struct _widgets *widgets);
GtkWidget* kahash_window_notebook_build_messages(struct _widgets *widgets);
GtkWidget* kahash_window_notebook_build_options(struct _widgets *widgets);
GtkWidget* kahash_window_notebook_build_log(struct _widgets *widgets);
GtkWidget* kahash_window_log_create();
GtkWidget* kahash_window_key_create();
void kahash_window_send_to_log(GtkWidget *view, gchar *message);

// cb
void cb_window_destroy(GtkWidget *widget, gpointer data);
void cb_toolbar_about(GtkWidget *widget, gpointer data);
void cb_toolbar_add(GtkWidget *widget, gpointer data);
void cb_toolbar_preference(GtkWidget *widget, gpointer data);
void cb_password_generation(GtkWidget *widget, gpointer data);

#endif
