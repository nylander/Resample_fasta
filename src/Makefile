CC = gcc
CFLAGS = -Wall -O3
DEPS = dynarray.h random.h quicksort.h
OBJ = dynarray.o main.o
PROG = prog3
RM = rm -v
INFILE = infile2

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(PROG)

test: $(PROG) $(INFILE)
	./$(PROG) $(INFILE)

