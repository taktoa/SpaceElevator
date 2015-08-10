OUTPUT_FOLDER = "bin/"
OUTPUT_EXEC = "oscil"

all: src/oscil.c src/util.c
	mkdir -p $(OUTPUT_FOLDER)
	gcc -o $(OUTPUT_FOLDER)/$(OUTPUT_EXEC) -O3 -fgnu89-inline -lGL -lGLU -lglut -lm -std=gnu99 -pedantic -Wall src/oscil.c src/util.c

clean:
	rm -f bin/*
