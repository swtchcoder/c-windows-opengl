CC=cc
CFLAGS=-Wall -Wextra -std=c99 -Iexternal/include
LIBS=-lopengl32 -lgdi32
SRC=main.c window.c external/src/gl.c
OBJ=$(SRC:.c=.o)