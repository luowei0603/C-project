.PHONY: clean

CFLAGS  := -Wall -Werror -g 
LD      := g++
LDLIBS  := ${LDLIBS} 

APPS    := Graph

all: ${APPS}

Graph: main.o MGraph.o GraphAdjList.o
	${LD} -o $@ $^ ${LDLIBS}

clean:
	rm -f *.o ${APPS}
