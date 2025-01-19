CC=gcc
CFLAGS= -g
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
TEST=tests
TESTS=$(wildcard $(TEST)/*.c)
TESTOBJS=$(patsubst $(TEST)/%.c, $(OBJ)/$(TEST)/%.o, $(TESTS))
TESTBIN=$(BINDIR)/test

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

run: $(BIN)
	./$(BIN)
clean:
	$(RM) $(BINDIR)/* $(OBJ)/*

debug: $(OBJS)
	$(CC) $(OBJS) -g -o $(BINDIR)/$@ $(CFLAGS)
