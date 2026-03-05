include config.mk

SRC=main.c window.c external/src/gl.c
OBJ=$(SRC:.c=.o)

all: program

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

program: $(OBJ) config.mk
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ) program