EXE = review
TEST = test

EXE_OBJ = main.o
OBJS = main.o ReviewParser.o Node.o Graph.o Methods.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk

GRAPH_OBJS = $(filter-out $(EXE_OBJ), $(OBJS))