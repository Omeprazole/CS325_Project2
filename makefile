#------------------------------------------------------------------------------
#prog: Run this command with one arugment. This program will input the
#  data from the file name of the argument and output running results of 3
#  algorithms into the output file.

#run: Run this command with no arguments.
#------------------------------------------------------------------------------
all: prog run

algorithms.o: algorithms.cpp algorithms.h 
	g++ -c algorithms.cpp

prog: algorithms.o main1.cpp
	g++ algorithms.o  main1.cpp -o prog

run: algorithms.o main2.cpp
	g++ algorithms.o  main2.cpp -o run

clean:
	rm algorithms.o	
	rm prog
	rm run
