/******************************************************************************
Read the specific input file from command line, get the coins of denominations
and amount of money to be made change from that file. Use three algorithms
calculate the minimize the total number of coins needed and the number of
coins it took on each denomination value. Output the results in another file
name [input filename]change.txt
******************************************************************************/
#include "algorithms.h"
#include <fstream>		
#include <iostream>		
#include <cstring>
#include <cstdio>		//printf
#include <stdlib.h>		//atoi
using namespace std;

//src:http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
void Tokenize(const string& str,
	vector<string>& tokens,
	const string& delimiters = " ")
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

//output the vector into a file with the formate "[c1, c2, ..., cn]"
void outputVector(ofstream& output, vector<int>& C){
	output << "[";
	for (int i = 0; i < C.size() - 1; i++){
		output << C[i] << ",";
	}
	output << C[C.size() - 1] << "]" << endl;
}

int main(int argc, char* argv[]) {
	//Check the number of argument
	if (argc != 2){
		cout << "Error, please input a file name as an argument." << endl;
		return 0;
	}

	ifstream input_file;
	string if_name(argv[1]);
	//Open the input file 
	input_file.open(if_name.c_str());

	//reading the file and convert each line into a vector
	if (!input_file.is_open()){
		cout << "Unable to open file." << endl;
		return -1;
	}

	string line;
	vector<vector<int> > rows;
	//line represent all characters in a line, which is cstring
	while (getline(input_file, line)){
		vector<string> row;
		vector<int> nums;
		Tokenize(line, row, " [],");
		for (int i = 0; i < row.size(); i++) {
			nums.push_back(atoi(row[i].c_str()));
		}
		rows.push_back(nums);
	}
	input_file.close();

	ofstream output_file;
	string of_name = if_name.replace(if_name.begin()
		+ if_name.find_last_of("."), if_name.end(), "change.txt");


	output_file.open(of_name.c_str());

	//Check if output file is open
	if (!output_file.is_open()){
		cout << "Unable to open file." << endl;
		return -1;
	}

	cout << "Waiting for output results into " << of_name << " file" << endl;
	//Output results of each algorithm in the file
	output_file << "Divide and Conquer Algorithm Result:" << endl;
	for (int i = 0; i < rows.size(); i += 2){
		vector<int> C = changeslow(rows[i], rows[i + 1][0]);
		outputVector(output_file, C);
		output_file << count(C) << endl;
		C.clear();
	}

	output_file << "\nGreedy Algorithm Result:" << endl;
	for (int i = 0; i < rows.size(); i += 2){
		vector<int> C = changegreedy(rows[i], rows[i + 1][0]);
		outputVector(output_file, C);
		output_file << count(C) << endl;
		C.clear();
	}

	output_file << "\nDynamic Programming Result:" << endl;
	for (int i = 0; i < rows.size(); i += 2){
		vector<int> C = changedp(rows[i], rows[i + 1][0]);
		outputVector(output_file, C);
		output_file << count(C) << endl;
		C.clear();
	}
	cout << "Done, results were outputted into the " << of_name << " file" << endl;

	output_file.close();
}
