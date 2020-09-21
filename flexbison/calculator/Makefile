CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -std=c11
CXXFLAGS=-Wall -Wextra -std=c++11
TARGET=calculator
SRCS=main.c lex.yy.c parser.tab.c
OBJS=main.o lex.yy.o parser.tab.o

.PHONY: default
default: all

.PHONY: all
all: $(TARGET)

parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: scanner.l
	flex scanner.l

parser.tab.c: parser.y
	bison parser.y

$(TARGET): $(OBJS)
	$(CC) $(CFALGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) -rf $(OBJS) $(TARGET)

