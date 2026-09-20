proc:proc.o
	gcc proc.o -o proc
proc.o:proc.s
	gcc -c  proc.s -o proc.o
proc.s:proc.i
	gcc -S proc.i -o proc.s
proc.i:proc.c
	gcc -E proc.c -o proc.i

.PHONY:clean
clean:
	rm -f *.i *.s *.o proc
	
