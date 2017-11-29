CC = gcc
#INCLUDEDIR = SFMT
#CFLAGS = -Wall -O3 -msse2 -DHAVE_SSE2 -DSFMT_MEXP=2281 -I$(INCLUDEDIR)
CFLAGS = -Wall -O3
LDFLAGS = -lz
DEPS = kseq.h twister.h SFMT.h dict.h
OBJ = mycode.o dict.o 
BIN = myprog

.PHONY: all clean test

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)

test: all
	./$(BIN) infile

