//	Copyright 2014 Wahankh <dev@wahankh.co.uk>
//	2014-11-22T10:59+00:00

#include "core.h"

gint main(gint argc, gchar **argv)
{
	if(kahash_core_initialize() == EXIT_FAILURE)
	{
		g_printf("[!] kahash_core_initialize() == FAILURE\n");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
