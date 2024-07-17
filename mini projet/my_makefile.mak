prog: Myshell.o 
    gcc -o prog Myshell.o -lreadline

progV2.o : Myshell.c
    gcc -c -Wall Myshell.c -lreadline

install :
    ./configure
    make
	make install

clean :
    rm -f prog *.o