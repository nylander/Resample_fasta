CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lz
DEPS = kseq.h randsamp.h
OBJ = mycode.o randsamp.o

.PHONY: all clean test

all: myprog

myprog: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm -f *.o myprog

test: all
	./myprog infile
