CC = gcc
CPPFLAGS = -I src
CFLAGS = -Wall -Wextra -std=c99 -m32 -g
RM = rm -f

BFCI_SOURCES = src/common.c src/bfci.c
BFCI_OBJECTS = $(BFCI_SOURCES:src%.c=obj%.o)
BFCI_TARGET = bin/bfci

.PHONY: default
default: all

.PHONY: all
all: $(BFCI_TARGET)

$(BFCI_TARGET): $(BFCI_OBJECTS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

$(BFCI_OBJECTS): $(BFCI_SOURCES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(BFCI_TARGET) $(BFCI_OBJECTS)

