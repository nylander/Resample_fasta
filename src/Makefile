CC = gcc
CFLAGS = -Wall -O3
DEPS = dynarray.h
OBJ = dynarray.o main.o
PROG = prog3
RM = rm -v

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(PROG)
