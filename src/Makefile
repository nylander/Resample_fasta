CC = gcc
CFLAGS = -Wall -O3
DEPS = dynarray.h 
OBJ = dynarray.o main.o
PROG = prog3
RM = rm -v
INFILE = infile

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g

debug: $(PROG)

test: $(PROG) $(INFILE)
	./$(PROG) $(INFILE)

clean:
	$(RM) $(OBJ) $(PROG)
