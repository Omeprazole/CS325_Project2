/**
 *This tool is used to generate CSV files that can easily be imported into Excel.
 *This allowed the group to quickly test multiple sets of data quickly and eliminated
 *the need input data one item at a time.
 **/
#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream> //used to read in the file
using namespace std;

void slow(vector <vector <int> > &V, vector <vector <int> > &A);
//Runs the slow algorithm for 4, 5a, 5b, and 6. 
void greedy(vector <vector <int> > &V, vector <vector <int> > &A);
//Runs the greedy algorithm for 4, 5a, 5b, and 6.
void dynamic(vector <vector <int> > &V, vector <vector <int> > &A);
//Runs the dynamic programing  algorithm for 4, 5a, 5b, and 6.
void runTime(int choice, vector <vector <int> > &V);
//Runs the algorithm on two different sets of denominations
//while calculating the run time
void runSlow(vector <vector <int> > &V);
//Since the slow algorithm is so inefficient we had to run the 
//algorithm on a much smaller set of data. To maintain integerity
//across all three algorithms we also ran Greedy and DP on this 
//data set as well
double getMilliseconds();
//Gets the current time count in milliseconds.

int main(int argc, char* argv[]) {
	ifstream file("reportValues.txt"); 
	//Opens the file with the test data
	if (!file.is_open()) {
		cout << "Couldn't open file";
		return 1;
	}
	vector <vector <int> > V;
	//this vector will hold the sets of denominations
	string line, value;
	for (int x = 0; x < 4; x++) { //Inputs all the arrays for V from file
		getline(file, line, '\n');
		stringstream ss(line);
		int i;
		vector <int> temp;
		while (ss >> i) {
			temp.push_back(i);
		}
		V.push_back(temp);
	}
	file.close();
	//will hold the amounts of cents to test against
	vector <vector <int> > A;
	vector <int> temp;
	int cents;
	//Builds the data set A for #4
	for (cents = 2010; cents <= 2200; cents += 5) {
		temp.push_back(cents);
	}
	A.push_back(temp);
	//Builds the data set A for for #5 & #6
	temp.clear();
	for (cents = 2000; cents <= 2200; cents++) {
		temp.push_back(cents);
	}
	A.push_back(temp);

	int choice;
	cout << "Pick your algorithm:\n";
	cout << "1. Slow\n";
	cout << "2. Greedy\n";
	cout << "3. Dynamic Programming\n";
	cout << "Choice: ";
	cin >> choice;

	switch (choice) {
	case 1:
		runSlow(V);
		break;
	case 2:
		greedy(V, A);
		break;
	case 3:
		dynamic(V, A);
		break;
	default:
		cout << "Not a valid choice\n";
	}
	//calls the function to calculate run time
	runTime(choice, V);
	cout << "Finished\n";

}

void runSlow(vector <vector <int> > &V)
{
	vector <int> temp;
	vector <vector <int> > A;
	int cents;
	//Builds data set for Slow for #4
	for (cents = 10; cents <= 30; cents += 5) {
		temp.push_back(cents);
	}
	A.push_back(temp);
	//Builds data set for Slow for #5 & #6
	temp.clear();
	for (cents = 10; cents <= 20; cents++) {
		temp.push_back(cents);
	}
	A.push_back(temp);
	slow(V,A); //runs the slow algorithm
	greedy(V, A); //runs the greedy algorithm
	dynamic(V, A); //runs the DP algorithm
}

void runTime(int choice, vector <vector <int> > &V)
{
	vector <int> A;
	int MIN, MAX; //used to generate evenly distributed values of A
	ofstream ofile;
	ofile.open("timing.csv"); //this is where the timing will be stored with A
	cout << "What is your min cents? ";
	cin >> MIN;
	cout << "What is your max cents? ";
	cin >> MAX;
	//This loop is not a perfect distribution method but is more than adequete for our purposes
	for (int x = MIN; x < MAX; x += (MAX - MIN) / 10 + 1) { //the +1 prevents adding 0 each time
		double t1 = getMilliseconds(); 
		//t1 will be used to calculate run time for the chosen algorithm
		for (int y = 0; y < 100; y++) {
			switch (choice){
			case 1:
				changeslow(V[0], x);
				break;
			case 2:
				changegreedy(V[0], x);
				break;
			case 3:
				changedp(V[0], x);
				break;
			default:
				cout << "Invalid Choice";
				break;
			}
		}
		double t2 = getMilliseconds() - t1; //total run time in ms
		cout << "Total Time for 100 loops: " << t2 << " A: " << x << endl; //shows result to screen
		ofile << x << "," << t2 << endl; //saves result to file

	}
	ofile.close();
	ofile.open("timing2.csv");
	//this loop runs the same algorithm but on a different set of denominations
	for (int x = MIN; x < MAX; x += (MAX - MIN) / 10 + 1) { //the +1 prevents adding 0 each time
		double t1 = getMilliseconds();
		for (int y = 0; y < 100; y++) {
			switch (choice){
			case 1:
				changeslow(V[2], x);
				break;
			case 2:
				changegreedy(V[2], x);
				break;
			case 3:
				changedp(V[2], x);
				break;
			default:
				cout << "Invalid Choice";
				break;
			}
		}
		double t2 = getMilliseconds() - t1;
		cout << "Total Time for 100 loops: " << t2 << " A: " << x << endl; //displays result
		ofile << x << "," << t2 << endl; //outputs to file

	}
	ofile.close();
}

void slow(vector <vector <int> > &V, vector <vector <int> > &A)
{
	//Runs the algorithm for #4
	ofstream ofile;
	cout << "Opening slow-report4.csv...";
	ofile.open("slow-report4.csv");
	for (int x = 0; x < A[0].size(); x++) {
		vector <int> C = changeslow(V[0], A[0].at(x));
		ofile << A[0].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing slow-report4.csv\n";
	//Runs the algorithm for #5a
	cout << "Opening slow-report5a.csv...";
	ofile.open("slow-report5a.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changeslow(V[1], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing slow-report5a.csv\n";
	//Runs the algorithm for #5b
	cout << "Opening slow-report5b.csv...";
	ofile.open("slow-report5b.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changeslow(V[2], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing slow-report5b.csv\n";
	//Runs the algorithm for #6
	cout << "opening slow-report6.csv...";
	ofile.open("slow-report6.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changeslow(V[3], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing slow-report6.csv\n";
}

void greedy(vector <vector <int> > &V, vector <vector <int> > &A)
{
	//Runs the algorithm for #4
	ofstream ofile;
	cout << "Opening greedy-report4.csv...";
	ofile.open("greedy-report4.csv");
	for (int x = 0; x < A[0].size(); x++) {
		vector <int> C = changegreedy(V[0], A[0].at(x));
		ofile << A[0].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing greedy-report4.csv\n";
	//Runs the algorithm for #5a
	cout << "Opening greedy-report5a.csv...";
	ofile.open("greedy-report5a.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changegreedy(V[1], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing greedy-report5a.csv\n";
	//Runs the algorithm for #5b
	cout << "Opening greedy-report5b.csv...";
	ofile.open("greedy-report5b.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changegreedy(V[2], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing greedy-report5b.csv\n";
	//Runs the algorithm for #6
	cout << "opening greedy-report6.csv...";
	ofile.open("greedy-report6.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changegreedy(V[3], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing greedy-report6.csv\n";
}

void dynamic(vector <vector <int> > &V, vector <vector <int> > &A)
{
	//Runs the algorithm for #4
	ofstream ofile;
	cout << "Opening dp-report4.csv...";
	ofile.open("dp-report4.csv");
	for (int x = 0; x < A[0].size(); x++) {
		vector <int> C = changedp(V[0], A[0].at(x));
		ofile << A[0].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing dp-report4.csv\n";
	//Runs the algorithm for #5a
	cout << "Opening dp-report5a.csv...";
	ofile.open("dp-report5a.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changedp(V[1], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing dp-report5a.csv\n";
	//Runs the algorithm for #5b
	cout << "Opening dp-report5b.csv...";
	ofile.open("dp-report5b.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changedp(V[2], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing dp-report5b.csv\n";
	//Runs the algorithm for #6
	cout << "opening dp-report6.csv...";
	ofile.open("dp-report6.csv");
	for (int x = 0; x < A[1].size(); x++) {
		vector <int> C = changedp(V[3], A[1].at(x));
		ofile << A[1].at(x) << "," << count(C) << "\n";
	}
	ofile.close();
	cout << "closing dp-report6.csv\n";
}

double getMilliseconds() {
	return 1000.0 * clock() / CLOCKS_PER_SEC;
}
