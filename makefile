all: hello

hello: main.o sqlite3.o
	g++ -o .\main.exe .\main.o .\sqlite3.o

main.o: main.cpp
	g++ -c .\main.cpp

sqlite3.o: sqlite3.c
	gcc -c .\sqlite3.c