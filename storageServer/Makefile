CC=g++
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	echo "hit"
	echo $<
	$(CC) -c $< -o $@

run: $(BIN)
	./$(BIN)
clean:
	$(RM) $(BINDIR)/* $(OBJ)/*

debug: $(OBJS)
	$(CC) $(OBJS) -g -o $(BINDIR)/$@ $(CFLAGS)
