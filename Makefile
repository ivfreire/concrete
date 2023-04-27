GCC		= gcc

INPUT	= src/main.c src/concrete.c

LIBS	= -lm -pthread -lSDL2main -lSDL2

OUTPUT	= concrete

all $(INPUT):
	$(GCC) -Wall $(INPUT) -o $(OUTPUT) $(LIBS)