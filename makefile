CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g

INCLUDES = -Iinclude

BINDIR = bin/
SRCDIR = src/

OBJDIR = obj/

SOURCE = $(SRCDIR)car.c $(SRCDIR)LinkedListApi.c $(SRCDIR)main.c

OBJS = $(OBJDIR)car.o $(OBJDIR)LinkedListApi.o $(OBJDIR)main.o

SOURCETEST = $(SRCDIR)car.c $(SRCDIR)LinkedListApi.c $(SRCDIR)testMain.c

OBJSTEST = $(OBJDIR)car.o $(OBJDIR)LinkedListApi.o $(OBJDIR)testMain.o

SRC_FILES = $(wildcard ./src/*.c)

BIN = ./bin/

PROGNAME = $(BINDIR)run



program:
	$(CC) $(CFLAGS) $(SOURCE) $(INCLUDES) -o $(BINDIR)run

tests:
	$(CC) $(CFLAGS) $(SOURCETEST) $(INCLUDES) -o $(BINDIR)runTest


clean:
	rm ./$(BINDIR)run ./$(BINDIR)runTest
