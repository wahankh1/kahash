//	Copyright 2014 Wahankh <dev@wahankh.co.uk>
//	2014-11-22T10:59+00:00

#include "core.h"

gint kahash_core_initialize()
{
	struct _widgets widgets;
	
	gtk_init(NULL, NULL);
	
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
}
