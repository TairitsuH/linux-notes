SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
BIN=processbar.exe

$(BIN):$(OBJ)
	gcc -o $@ $^

%.o:%.c
	gcc -c $<

.PHONY:
clean:
	rm -f $(BIN) $(OBJ)
