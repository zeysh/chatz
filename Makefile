CC = gcc
BIN = bin
INSTALL = /usr/bin
CFLAGS = -std=gnu99 -W -Wall
GTKFLAGS=`pkg-config --cflags --libs gtk+-3.0`
SRC = src/main.c \
      src/networking.c

all: chatz

chatz:
	$(CC) $(CFLAGS) $(SRC) $(GTKFLAGS) -o $(BIN)/chatz $(LIBS)

install:
	@install $(BIN)/chatz $(INSTALL)

clean:
	$(RM) $(BIN)/chatz
