//	Copyright 2014 Wahankh <dev@wahankh.co.uk>
//	2014-11-22T10:59+00:00

#ifndef CORE_H
#define CORE_H

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include "common.h"
#include "window.h"

struct _kahash_key {
	gchar *name;
	gchar *password;
};

gint kahash_core_initialize();
void kahash_core_initialize_random();
void kahash_core_random_string(gchar *string, gint length);

#endif
