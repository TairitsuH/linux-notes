BIN=myshell
SRC=$(wildcard *.cc)
OBJ=$(SRC:.cc=.o)

$(BIN):$(OBJ)
	g++ -o $@ $^

.PHONY:clean

clean:
	rm -f $(OBJ) $(BIN)



