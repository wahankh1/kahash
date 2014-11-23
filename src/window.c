//	Copyright 2014 Wahankh <dev@wahankh.co.uk>
//	2014-11-22T10:59+00:00

#include "window.h"

gint kahash_window_build(struct _widgets *widgets)
{
	// window
	widgets->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(widgets->window), APP_NAME);
	gtk_widget_set_size_request(widgets->window, 300, 500);
	//gtk_window_set_resizable(GTK_WINDOW(widgets->window), FALSE);
	g_signal_connect(widgets->window, "destroy", G_CALLBACK(cb_window_destroy), widgets);
	
	// grid
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_container_add(GTK_CONTAINER(widgets->window), grid);
	
	// toolbar
	kahash_window_toolbar_build(widgets);
	gtk_grid_attach(GTK_GRID(grid), widgets->toolbar, 0, 0, 1, 1);
	
	// notebook
	kahash_window_notebook_build(widgets);
	gtk_grid_attach(GTK_GRID(grid), widgets->notebook, 0, 1, 1, 1);
	
	// statusbar
	widgets->statusbar = gtk_statusbar_new();
	gtk_grid_attach(GTK_GRID(grid), widgets->statusbar, 0, 2, 1, 1);
	
	send_to_log(widgets->log_in_view, g_strdup_printf("%s %s\n%s", APP_NAME, APP_VERSION, APP_BUILD));
	
	return EXIT_SUCCESS;
}

void kahash_window_toolbar_build(struct _widgets *widgets)
{
	// toolbar
	widgets->toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(widgets->toolbar), GTK_TOOLBAR_ICONS);
	
	// home
	widgets->toolbar_btn_home = gtk_tool_button_new_from_stock(GTK_STOCK_HOME);
	gtk_toolbar_insert(GTK_TOOLBAR(widgets->toolbar), widgets->toolbar_btn_home, -1);
	g_signal_connect(widgets->toolbar_btn_home, "clicked", G_CALLBACK(cb_toolbar_home), widgets);
	
	gtk_toolbar_insert(GTK_TOOLBAR(widgets->toolbar), gtk_separator_tool_item_new(), -1);
	
	// preferences
	widgets->toolbar_btn_preference = gtk_tool_button_new_from_stock(GTK_STOCK_PREFERENCES);
	gtk_toolbar_insert(GTK_TOOLBAR(widgets->toolbar), widgets->toolbar_btn_preference, -1);
	g_signal_connect(widgets->toolbar_btn_preference, "clicked", G_CALLBACK(cb_toolbar_preference), widgets);
	
	gtk_toolbar_insert(GTK_TOOLBAR(widgets->toolbar), gtk_separator_tool_item_new(), -1);
	
	// about
	widgets->toolbar_btn_about = gtk_tool_button_new_from_stock(GTK_STOCK_ABOUT);
	gtk_toolbar_insert(GTK_TOOLBAR(widgets->toolbar), widgets->toolbar_btn_about, -1);
	g_signal_connect(widgets->toolbar_btn_about, "clicked", G_CALLBACK(cb_toolbar_about), widgets);
}

void kahash_window_notebook_build(struct _widgets *widgets)
{
	GtkWidget *notebook_page_one, *notebook_page_two, *notebook_page_three;
	GtkWidget *notebook_page_one_label, *notebook_page_two_label, *notebook_page_three_label;
	
	widgets->notebook = gtk_notebook_new();
	gtk_widget_set_vexpand(widgets->notebook, TRUE);
	
	// page one
	notebook_page_one = kahash_window_notebook_build_page1(widgets);
	notebook_page_one_label = gtk_label_new("Messages");
	gtk_label_set_width_chars(GTK_LABEL(notebook_page_one_label), 10);
	gtk_notebook_insert_page(GTK_NOTEBOOK(widgets->notebook), notebook_page_one, notebook_page_one_label, -1);
	
	// page two
	notebook_page_two = kahash_window_notebook_build_page2(widgets);
	notebook_page_two_label = gtk_label_new("Options");
	gtk_label_set_width_chars(GTK_LABEL(notebook_page_two_label), 10);
	gtk_notebook_insert_page(GTK_NOTEBOOK(widgets->notebook), notebook_page_two, notebook_page_two_label, -1);
	
	// page three
	notebook_page_three = kahash_window_notebook_build_page3(widgets);
	notebook_page_three_label = gtk_label_new("Log");
	gtk_label_set_width_chars(GTK_LABEL(notebook_page_three_label), 10);
	gtk_notebook_insert_page(GTK_NOTEBOOK(widgets->notebook), notebook_page_three, notebook_page_three_label, -1);
}

GtkWidget* kahash_window_notebook_build_page1(struct _widgets *widgets)
{
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// scrolled
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_vexpand(scrolled_window, TRUE);
	gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 0, 1, 1);
	
	// view
	widgets->message_in_view = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets->message_in_view), FALSE);
	gtk_container_add(GTK_CONTAINER(scrolled_window), widgets->message_in_view);
	
	// entry
	widgets->message_of_input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), widgets->message_of_input, 0, 1, 1, 1);
	
	return grid;
}

GtkWidget* kahash_window_notebook_build_page2(struct _widgets *widgets)
{
	GtkWidget *grid = gtk_grid_new();
	return grid;
}

GtkWidget* kahash_window_notebook_build_page3(struct _widgets *widgets)
{
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	
	widgets->log_in_view = kahash_window_log_create();
	gtk_container_add(GTK_CONTAINER(scrolled_window), widgets->log_in_view);
	
	return scrolled_window;
}

GtkWidget* kahash_window_log_create()
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *render;
	GtkWidget *tree;
	GtkListStore *store;
	
	tree = gtk_tree_view_new();
	render = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Log", render, "text", LOG_TXT, NULL);
	
	gtk_tree_view_column_set_expand(column, 1);
	gtk_tree_view_insert_column(GTK_TREE_VIEW(tree), column, -1);
	store = gtk_list_store_new(LOG_NUM, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(store));
	
	g_object_unref(store);
	return tree;
}

GtkWidget* kahash_window_key_create()
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *render;
	GtkWidget *tree;
	GtkListStore *store;
	
	tree = gtk_tree_view_new();
	
	// id
	render = gtk_cell_renderer_text_new();	
	column = gtk_tree_view_column_new_with_attributes("Id", render, "text", KEY_ID, NULL);
	gtk_tree_view_insert_column(GTK_TREE_VIEW(tree), column, -1);
	
	// name
	render = gtk_cell_renderer_text_new();	
	column = gtk_tree_view_column_new_with_attributes("Name", render, "text", KEY_NAME, NULL);
	gtk_tree_view_insert_column(GTK_TREE_VIEW(tree), column, -1);
	
	store = gtk_list_store_new(LOG_NUM, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(store));
	
	g_object_unref(store);
	
	return tree;
}

void send_to_log(GtkWidget *view, gchar *message)
{
	GtkListStore *store;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(view)));
	
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, LOG_TXT, message, -1);
}

//
//	callbacks
//
void cb_window_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void cb_toolbar_about(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog_about = gtk_about_dialog_new();
	
	//
	const gchar *author[] = {
		"Wahankh <dev@wahankh.co.uk>",
		NULL
	};
	
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog_about), APP_NAME);
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog_about), APP_VERSION);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog_about), "Copyright © 2014 Wahankh");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog_about), "comments");
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog_about), "LICENSE");
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog_about), GTK_LICENSE_CUSTOM);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog_about), "https://github.com/wahankh1/kahash");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog_about), "https://github.com/wahankh1/kahash");
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog_about), author);
	//gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog_about), "");
	
	//
	gtk_dialog_run(GTK_DIALOG(dialog_about));
	gtk_widget_destroy(dialog_about);
}

void cb_toolbar_home(GtkWidget *widget, gpointer data)
{
	struct _widgets *widgets = data;
	GtkWidget *dialog, *content;
	gint response;
	
	dialog = gtk_dialog_new_with_buttons(
		"Keys", 
		GTK_WINDOW(widgets->window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_STOCK_OK,
		GTK_RESPONSE_OK,
		GTK_STOCK_CLOSE,
		GTK_RESPONSE_CLOSE,
		NULL);
		
	content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	
	// content
	GtkWidget *grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content), grid);
	
	// key view
	GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled), 250);
	
	widgets->key_store_view = kahash_window_key_create();
	gtk_container_add(GTK_CONTAINER(scrolled), widgets->key_store_view);
	gtk_grid_attach(GTK_GRID(grid), scrolled, 0, 0, 1, 4);
	
	// name
	GtkWidget *name_label = gtk_label_new("Name:");
	gtk_label_set_width_chars(GTK_LABEL(name_label), 10);
	gtk_grid_attach(GTK_GRID(grid), name_label, 1, 0, 1, 1);
	
	GtkWidget *name_entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), name_entry, 2, 0, 1, 1);
	
	// password
	GtkWidget *password_label = gtk_label_new("Password:");
	gtk_grid_attach(GTK_GRID(grid), password_label, 1, 1, 1, 1);
	
	GtkWidget *password_entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), password_entry, 2, 1, 1, 1);
	
	// size
	GtkWidget *size_label = gtk_label_new("Size:");
	gtk_grid_attach(GTK_GRID(grid), size_label, 1, 2, 1, 1);
	
	GtkWidget *size_entry = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(size_entry), NULL, "512");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(size_entry), NULL, "1024");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(size_entry), NULL, "2048");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(size_entry), NULL, "4096");
	gtk_combo_box_set_active(GTK_COMBO_BOX(size_entry), 1);
	gtk_grid_attach(GTK_GRID(grid), size_entry, 2, 2, 1, 1);
	
	// buttonbox
	GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(grid), button_box, 1, 3, 2, 1);
	
	// add
	GtkWidget *button_add = gtk_button_new();
	gtk_widget_set_tooltip_text(button_add, "Make and add");
	GtkWidget *icon_add = gtk_image_new_from_stock(GTK_STOCK_ADD, GTK_ICON_SIZE_BUTTON);
	gtk_button_set_image(GTK_BUTTON(button_add), icon_add);
	gtk_box_pack_start(GTK_BOX(button_box), button_add, FALSE, FALSE, 5);
	
	// generate
	GtkWidget *button_generate = gtk_button_new();
	gtk_widget_set_tooltip_text(button_generate, "Generate password");
	GtkWidget *icon_generate = gtk_image_new_from_stock(GTK_STOCK_EXECUTE, GTK_ICON_SIZE_BUTTON);
	gtk_button_set_image(GTK_BUTTON(button_generate), icon_generate);
	gtk_box_pack_start(GTK_BOX(button_box), button_generate, FALSE, FALSE, 5);
	
	// endcontent 
	
	gtk_widget_show_all(dialog);
	response = gtk_dialog_run(GTK_DIALOG(dialog));
	
	switch(response)
	{
		case GTK_RESPONSE_OK:
			break;
			
		case GTK_RESPONSE_CLOSE:
			break;
			
		default:
			break;
	}
	
	gtk_widget_destroy(dialog);
}

void cb_toolbar_preference(GtkWidget *widget, gpointer data)
{
}
