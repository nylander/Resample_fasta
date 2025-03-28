# Makefile for resample_fasta.c
# Fre 28 mar 2025
# Johan.Nylander@nrm.se

CC     = gcc
GDB    = gdb
CFLAGS = -Wall -O3
SRC    = resample_fasta.c
OBJ    = $(SRC:%.c=%.o)
PROG   = refast
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


