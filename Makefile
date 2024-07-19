# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -Iinclude

# Target binary
TARGET = xtask

# Source files
SRCS = src/xtask.c

# Libraries to link
LIBS = -lncurses

# Install directory
PREFIX = /usr/local

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Install the binary
install: $(TARGET)
	install -d $(PREFIX)/bin
	install $(TARGET) $(PREFIX)/bin

# Uninstall the binary
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

# Clean up
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all install uninstall clean
