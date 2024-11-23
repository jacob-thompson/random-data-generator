CC=gcc
CFLAGS=-I.
DEPS = generator.h
OBJ = main.o generator.o
OUT = random-data-generator
.PHONY: clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ) $(OUT) output.csv
