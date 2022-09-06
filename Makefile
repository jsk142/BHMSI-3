#
# Makefile for P3
# COSC 051
# Spring 2019
#

a.out: main.o
	g++ main.o

main.o: main.cpp
	g++ -c main.cpp

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip main.cpp Makefile

clean:
	rm -f *.o core a.out
