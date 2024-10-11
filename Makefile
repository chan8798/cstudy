main_exe:remake.o main.o hexfind.o errorfile.o
	gcc -o main_exe remake.o main.o hexfind.o errorfile.o

remake.o:remake.c
	gcc -c -o remake.o remake.c   
hexfind.o : hexfind.c
	gcc -c -o hexfind.o hexfind.c
errorfile.o : errorfile.c
	gcc -c -o errorfile.o errorfile.c
main.o : main.c
	gcc -c -o main.o main.c

clean:
	del *.exe *.o *test.txt

