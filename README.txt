For this project we created two programs to help us complete all the 
requirements. To make both programs use "make all"

The first program is "prog" (main1.cpp). In order to run this file
must be compiled with algorithms.cpp and algorithms.h. To run the program 
it must be called with the input file as the one and only argument. The 
program will run each algorithm using the data from the input file and 
output the results into [input filename]change.txt. Testing.txt and 
Amount.txt have been provided for testing purposes.

The second program is "run" (main2.cpp). This program must be compiled with 
algorithms.cpp and algorithms.h. The program does not require an
argument. This program requires a file called reportValues.txt in 
order to run. The values in reportValues.txt will be used to run
a user chosen algorithm. The chosen algorithm will be run on data
to answer the questions from the report. All results will be outputted
in CSV files to make inputting data into Excel much faster. When
selecting to run the Slow algorithm it will run all three algorithms
using smaller data than found in reportsValues.txt.
