//	Copyright 2014 Wahankh <dev@wahankh.co.uk>
//	2014-11-22T10:59+00:00

#include "core.h"

gint kahash_core_initialize()
{
	struct _widgets widgets;
	
	gtk_init(NULL, NULL);
	
	kahash_core_initialize_random();
	
	// build
	if(kahash_window_build(&widgets) == EXIT_FAILURE)
	{
		g_printf("[!] kahash_window_build() == FAILURE\n");
		return EXIT_FAILURE;
	}
	
	gtk_widget_show_all(widgets.window);
	gtk_main();
	
	return EXIT_SUCCESS;
}

void kahash_core_initialize_random()
{
	guint32 seed;
	
	seed = g_random_int_range(0, G_MAXUINT32);
	
	srand(seed);
}

void kahash_core_random_string(gchar *string, gint length)
{
	while(length--)
	{
		string[length] = rand() % 94 + 33;
	}
}
