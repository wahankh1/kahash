#  Makefile
#  
#  Copyright 2014 Wahankh <dev@wahankh.co.uk>
#  
#  2014-11-22T09:38+00:00

TARGET=kahash

CC=gcc
CFLAGS=-Wall -I. -lcrypto -lssl `pkg-config --cflags --libs glib-2.0 gtk+-3.0`

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=obj/%.o)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)
	
$(OBJ) : obj/%.o : src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY: clean
clean:
	rm -f obj/* $(TARGET)
