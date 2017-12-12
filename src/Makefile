CC = gcc
GDB = gdb
CFLAGS = -Wall -O3
OBJ = resample_fasta.o
PROG = refas
RM = rm -v
INFILE = infile

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g

debug: $(PROG)
	$(GDB) ./$(PROG)

test: $(PROG) $(INFILE)
	./$(PROG) $(INFILE)

clean:
	$(RM) $(OBJ) $(PROG)
