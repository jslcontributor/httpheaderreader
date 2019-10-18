#
# Makefile for header counter projeect
#
#

main : main.o hashTable.o
	cc -o main main.o

main.o : main.c projStrings.h
	cc -c main.c

clean :
	rm main main.o hashTable.o

