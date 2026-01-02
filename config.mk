CC=cc
CFLAGS=-Wall -Wextra -pedantic -std=c99
LIBS=-lopengl32 -lgdi32
SRC=main.c window.c
OBJ=$(SRC:.c=.o)