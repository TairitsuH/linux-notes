BIN=testzom
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

$(BIN):$(OBJ)
	gcc -o $@ $^

.PHONY:clean

clean:
	rm -f $(OBJ) $(BIN)
