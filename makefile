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
ALGS        := Wave DBScan

HDR_ALGS  := $(patsubst %, $(HDR)/$(ALG_FOLDER)/%.h, $(ALGS))
OBJ_ALGS  := $(patsubst %, $(OBJ)/%.o, $(ALGS))
DATA_ALGS := $(patsubst %, $(DATA)/%, $(ALGS))

#message:
	#@echo $(HDR_ALGS)

SUBDATA := $(DATA)/all $(DATA)/histograms $(DATA)/graphs $(DATA_ALGS)

#Compiler features
CC     := g++ -c
LD	   := g++
CFLAGS := -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align \
		  -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security \
		  -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long  \
		  -Wcast-qual -Wno-suggest-attribute=format -Wpedantic \
		  -Wmissing-declarations -I$(HDR) -I$(HDR)/$(ALG_FOLDER)

#Variables
EXE    := $(BIN)/main
R_OBJS := main.o point.o cluster.o field.o  \
		  clustergenerator.o algorithm.o    \
		  gnuplot.o interface.o             \
		  logger.o parser.o  token.o controller.o
OBJS := $(patsubst %.o, $(OBJ)/%.o, $(R_OBJS))

$(EXE): $(OBJS) $(OBJ_ALGS)| $(BIN) $(DATA) $(SUBDATA)
	$(LD) $^ -o $@

$(OBJ)/main.o : $(SRC)/main.cpp $(OBJ)/interface.o | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJ)/clustergenerator.o : $(SRC)/clustergenerator.cpp $(HDR)/clustergenerator.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/controller.o : $(SRC)/controller.cpp $(HDR)/controller.h $(OBJ)/field.o $(OBJ_ALGS) $(OBJ)/logger.o $(OBJ)/algorithm.o $(OBJ)/clustergenerator.o $(OBJ)/gnuplot.o $(HDR)/token.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_ALGS): $(OBJ)/%.o : $(SRC)/$(ALG_FOLDER)/%.cpp $(HDR)/$(ALG_FOLDER)/%.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/interface.o : $(SRC)/interface.cpp $(HDR)/interface.h $(OBJ)/controller.o $(OBJ)/logger.o $(OBJ)/parser.o | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/logger.o : $(SRC)/logger.cpp $(HDR)/logger.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/parser.o : $(SRC)/parser.cpp $(HDR)/parser.h $(OBJ)/token.o | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/token.o : $(SRC)/token.cpp $(HDR)/token.h $(OBJ)/controller.o | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/gnuplot.o : $(SRC)/gnuplot.cpp $(HDR)/gnuplot.h $(HDR)/controller.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/field.o : $(SRC)/field.cpp $(HDR)/field.h $(OBJ)/point.o $(OBJ)/algorithm.o | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/algorithm.o : $(SRC)/algorithm.cpp $(HDR)/algorithm.h $(OBJ)/cluster.o $(HDR)/matrix.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/cluster.o : $(SRC)/cluster.cpp $(HDR)/cluster.h $(OBJ)/point.o | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/point.o : $(SRC)/point.cpp $(HDR)/point.h | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(BIN) $(OBJ) $(DATA) $(SUBDATA):
	$(MKDIR) $@

.PHONY: clean debug release

debug: CFLAGS += -DDEBUG -g -O0 
debug: $(EXE)

release: CFLAGS += -DRELEASE -O3 
release: $(EXE)

clean:
	$(RMDIR) $(OBJ) $(BIN) $(DATA) ./log.txt ./help.txt