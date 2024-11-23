CC=gcc
CFLAGS=-I.
DEPS = generator.h
OBJ = main.o generator.o
OUT = random-data-generator.exe
.PHONY: clean

%.o: %.c $(DEPS) clean
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	del main.o
	del generator.o
	del random-data-generator.exe
	del output.csv