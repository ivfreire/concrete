GCC		= gcc

INPUT	= src/main.c src/concrete.c

LIBS	= -lm -pthread

OUTPUT	= concrete

all $(INPUT):
	$(GCC) -Wall $(INPUT) -o $(OUTPUT) $(LIBS)