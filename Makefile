#
# Makefile
# Johan Nylander, 2025-03-28
#

CC = gcc

CFLAGS = -Wall -O3

SRC_DIR = src
SRC_FILE = $(SRC_DIR)/resample_fasta.c
TARGET = refast

BUILD_DIR = build

PROG = $(BUILD_DIR)/$(TARGET)
INFILE = data/infile

PREFIX ?= /usr/local
INSTALL_DIR = $(PREFIX)/bin

all: $(PROG)

$(PROG): $(SRC_FILE)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(PROG) $(SRC_FILE)

test: $(PROG)
	$(PROG) $(INFILE)

install: $(PROG)
	install -d $(INSTALL_DIR)
	install $(PROG) $(INSTALL_DIR)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Available targets:"
	@echo "  all      - Compile the source code"
	@echo "  test     - Run the program on the input file"
	@echo "  install  - Install the executable in $(INSTALL_DIR)"
	@echo "             Change destination by setting PREFIX. Default: $(PREFIX)"
	@echo "  clean    - Remove the build directory and the executable"
	@echo "  help     - Display this help message"
