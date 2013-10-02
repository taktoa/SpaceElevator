OUTPUT_EXEC = "bin/oscil"

all: src/oscil.c src/util.c
	gcc -o $(OUTPUT_EXEC) -O3 -fgnu89-inline -lGL -lGLU -lglut -lm -std=gnu99 -pedantic -Wall src/oscil.c src/util.c

clean:
	rm -f bin/*
