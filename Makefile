#
# Makefile for header counter projeect
#
#

main : main.o hashTable.o
	gcc -o main main.o

main.o : main.c projStrings.h
	gcc -c -g main.c

clean :
	rm main main.o hashTable.o

