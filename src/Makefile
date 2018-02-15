# Makefile for resample_fasta.c
# Thu 15 Feb 2018 10:43:56 AM CET
# Johan.Nylander@{nrm|nbis}.se

CC     = gcc
GDB    = gdb
CFLAGS = -Wall -O3
SRC    = resample_fasta.c
OBJ    = $(SRC:%.c=%.o)
PROG   = refas
RM     = rm -f
INFILE = ../data/infile

.PHONY: all debug test clean

all: $(PROG)

$(OBJ): $(SRC)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

debug: CFLAGS += -g

debug: $(PROG)
	$(GDB) ./$(PROG)

test: $(PROG) $(INFILE)
	@ ./$(PROG) $(INFILE)

clean:
	@ $(RM) $(OBJ) $(PROG)


