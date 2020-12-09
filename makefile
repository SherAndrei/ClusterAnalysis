#Commands
MKDIR := mkdir
RMDIR := rm -rf

#Folders to make life easier
BIN    := ./bin
OBJ    := ./obj
HDR    := ./include
SRC    := ./src
DATA   := ./data

ALG_FOLDER  := algorithms
ALGS        := Wave DBScan KMeans Hierarchical FOREL EM

HDR_ALGS  := $(patsubst %, $(HDR)/$(ALG_FOLDER)/%.h, $(ALGS))
OBJ_ALGS  := $(patsubst %, $(OBJ)/%.o, $(ALGS))
DATA_ALGS := $(patsubst %, $(DATA)/%, $(ALGS))

SUBDATA := $(DATA)/all $(DATA)/histograms $(DATA)/graphs $(DATA_ALGS)

#Compiler features
CC     := g++ -c
LD	   := g++
CFLAGS := -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -Wmissing-declarations -I$(HDR) -I$(HDR)/$(ALG_FOLDER)

#Variables
EXE  := $(BIN)/main
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

all : debug

$(EXE): $(OBJS) $(OBJ_ALGS)| $(BIN) $(DATA) $(SUBDATA)
	$(LD) $^ -o $@

$(OBJ)/main.o : $(SRC)/main.cpp $(HDR)/interface.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJ)/clustergenerator.o : $(SRC)/clustergenerator.cpp $(HDR)/clustergenerator.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/controller.o : $(SRC)/controller.cpp $(HDR)/controller.h $(HDR)/field.h $(OBJ_ALGS) $(HDR)/logger.h $(HDR)/algorithm.h $(HDR)/clustergenerator.h $(HDR)/gnuplot.h $(HDR)/token.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_ALGS): $(OBJ)/%.o : $(SRC)/$(ALG_FOLDER)/%.cpp $(HDR)/$(ALG_FOLDER)/%.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/interface.o : $(SRC)/interface.cpp $(HDR)/interface.h $(HDR)/controller.h $(HDR)/logger.h $(HDR)/parser.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/logger.o : $(SRC)/logger.cpp $(HDR)/logger.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/parser.o : $(SRC)/parser.cpp $(HDR)/parser.h $(HDR)/token.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/token.o : $(SRC)/token.cpp $(HDR)/token.h $(HDR)/controller.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/gnuplot.o : $(SRC)/gnuplot.cpp $(HDR)/gnuplot.h $(HDR)/controller.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/field.o : $(SRC)/field.cpp $(HDR)/field.h $(HDR)/point.h $(HDR)/algorithm.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/algorithm.o : $(SRC)/algorithm.cpp $(HDR)/algorithm.h $(HDR)/cluster.h $(HDR)/matrix.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/cluster.o : $(SRC)/cluster.cpp $(HDR)/cluster.h $(HDR)/point.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/point.o : $(SRC)/point.cpp $(HDR)/point.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(BIN) $(OBJ) $(DATA) $(SUBDATA):
	$(MKDIR) $@

.PHONY: clean cleandata debug release all

debug: CFLAGS += -DDEBUG -g -O0 
debug: $(EXE)

release: CFLAGS += -DRELEASE -O3 
release: $(EXE)

clean:
	$(RMDIR) $(OBJ) $(BIN) $(DATA) ./log.txt ./help.txt

cleandata:
	$(RMDIR) $(DATA)/*/*.dat $(DATA)/*/plot.p
	