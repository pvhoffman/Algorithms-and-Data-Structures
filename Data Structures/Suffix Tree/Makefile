PROJECT=suffix-tree
CC=g++
INCLUDES=-I. -I../../
CXXFLAGS=-g -Wall $(INCLUDES)
LFLAGS=
LIBS=
SRCS = main.cc suffix-tree.cc
OBJS = $(SRCS:.cc=.o)


all: $(PROJECT)


$(PROJECT): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(PROJECT) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	$(RM) *.o *~ $(PROJECT)

