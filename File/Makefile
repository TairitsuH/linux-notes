BIN=testfile
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

$(BIN):$(OBJ)
	gcc -g -o $@ $^

.PHONY:clean

clean:
	rm -f $(OBJ) $(BIN)



