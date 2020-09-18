#Commands
MKDIR := mkdir
RMDIR := rm -rf

#Folders to make life easier
BIN 	:= ./bin
OBJ 	:= ./obj
INCLUDE := ./include
SRC 	:= ./src

#Compiler features
CC     := g++
CFLAGS := -g -O0 -Werror -Wextra -Wpedantic -Wall -I$(INCLUDE)

#Variables
EXE  := $(BIN)/main
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))	

# $@ - the left side of the :
# $^ - the right side of the :
# $< - the first item in the dependencies list
# -c flag says to generate the object file

$(EXE): $(OBJS) | $(BIN)
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN) $(OBJ):
	$(MKDIR) $@

.PHONY: clean

clean:
	$(RMDIR) $(OBJ) $(BIN)