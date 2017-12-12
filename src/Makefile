CC = gcc
CFLAGS = -Wall -O3
OBJ = resample_fasta.o
PROG = resample_fasta
RM = rm -v
INFILE = infile

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g

debug: $(PROG)

test: $(PROG) $(INFILE)
	./$(PROG) $(INFILE)

clean:
	$(RM) $(OBJ) $(PROG)
