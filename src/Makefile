# Makefile for resample_fasta.c
# Tue 12 Dec 2017 10:44:59 AM CET
# Johan.Nylander@{nrm|nbis}.se

CC = gcc
GDB = gdb
CFLAGS = -Wall -O3
OBJ = resample_fasta.o
PROG = refas
RM = rm -v
INFILE = ../data/infile

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g

debug: $(PROG)
	$(GDB) ./$(PROG)

test: $(PROG) $(INFILE)
	@ ./$(PROG) $(INFILE)

clean:
	@ $(RM) $(OBJ) $(PROG)


