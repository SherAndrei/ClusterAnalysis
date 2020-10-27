#Commands
MKDIR := mkdir
RMDIR := rm -rf

#Folders to make life easier
BIN 	:= ./bin
OBJ 	:= ./obj
HDR     := ./include
SRC 	:= ./src

DATA    := ./data

OBJALGS  := ./obj/algorithms
HDRALGS  := ./include/algorithms
SRCALGS	 := ./src/algorithms
HDRSALGS := $(wildcard ${HDRALGS}/*.h)
DATAALGS := $(patsubst ${HDRALGS}/%.h, ${DATA}/%, ${HDRSALGS})


#Compiler features
CC     := g++
CFLAGS := -Werror -Wextra -Wpedantic -Wall -I$(HDR) -I${HDRALGS}

#Variables
EXE  := $(BIN)/main
SRCS := $(wildcard $(SRC)/*.cpp ${SRCALGS}/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))	

# $@ - the left side of the :
# $^ - the right side of the :
# $< - the first item in the dependencies list
# -c flag says to generate the object file

$(EXE): $(OBJS) | $(BIN) $(DATA) ${DATAALGS}
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ) ${OBJALGS}
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN) $(OBJ) ${OBJALGS} $(DATA) ${DATAALGS}:
	$(MKDIR) $@

.PHONY: clean debug release

debug: CFLAGS += -DDEBUG -g -O0 
debug: $(EXE)

release: CFLAGS += -DRELEASE -O3 
release: $(EXE)

clean:
	$(RMDIR) $(OBJ) $(BIN) $(DATA)