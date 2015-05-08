#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

void slow(vector <vector <int> > &V, vector <vector <int> > &A);
void greedy(vector <vector <int> > &V, vector <vector <int> > &A);
void dynamic(vector <vector <int> > &V, vector <vector <int> > &A);
void runTime(int choice, vector <vector <int> > &V);

double getMilliseconds() {
	return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]) {
  ifstream file("reportValues.txt");
  if(!file.is_open()) {
    cout << "Couldn't open file";
    return 1;
  }
  vector <vector <int> > V;
  vector <vector <int> > A;
  string line, value;
  for(int x = 0; x < 4; x++) {
    getline(file, line, '\n');
    stringstream ss(line);
    int i;
    vector <int> temp;
    while(ss >> i) {
      temp.push_back(i);
    }
    V.push_back(temp);
  }
  file.close();
  /*for(int x = 0; x < 4; x++) {
    for(int y = 0; y < V[x].size(); y++) {
      cout << V[x].at(y) << " ";
    }
    cout << endl;
    }*/
  vector <int> temp;
  int cents;
  //for #4
  for(cents = 2010; cents <= 2200; cents += 5) {
    temp.push_back(cents);
  } 
  A.push_back(temp);
  //for #5 & #6
  temp.empty();
  for(cents = 2000; cents <= 2200; cents++) {
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

  switch(choice) {
  case 1:
    cout << "Too slow to use the same values\n";
    //slow(V,A);
    break;
  case 2:
    greedy(V,A);
    break;
  case 3:
    dynamic(V,A);
    break;
  default:
    cout << "Not a valid choice\n";
  }
  runTime(choice, V);
  cout << "Finished\n";

}

void runTime(int choice, vector <vector <int> > &V)
{
  vector <int> A;
  int MIN, MAX;
  cout << "What is yoru min cents? ";
  cin >> MIN;
  cout << "What is your max cents? ";
  cin >> MAX;

  for(int x = MIN; x < MAX; x += (MAX - MIN)/10 + 1) { //the +1 prevents adding 0 each time
    double t1 = getMilliseconds();
    for(int y = 0; y < 100; y++) {
      switch(choice){
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
    double t2 = getMilliseconds() - t1;
    cout << "Total Time for 100 loops: " << t2 << " A: " << x << endl;
  }
}

void slow(vector <vector <int> > &V, vector <vector <int> > &A)
{
  //#4
  ofstream ofile;
  cout << "Opening slow-report4.csv...";
  ofile.open("slow-report4.csv");
  for(int x = 0; x < A[0].size(); x++) {
    vector <int> C = changeslow(V[0], A[0].at(x));
    ofile << A[0].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing slow-report4.csv\n";
  //#5a
  cout << "Opening slow-report5a.csv...";
  ofile.open("slow-report5a.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changeslow(V[1], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing slow-report5a.csv\n";
  //#5b
  cout << "Opening slow-report5b.csv...";
  ofile.open("slow-report5b.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changeslow(V[2], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing slow-report5b.csv\n";
  //#6
  cout << "opening slow-report6.csv...";
  ofile.open("slow-report6.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changeslow(V[3], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing slow-report6.csv\n";
}

void greedy(vector <vector <int> > &V, vector <vector <int> > &A)
{
  cout << "test";
  //#4
  ofstream ofile;
  cout << "Opening greedy-report4.csv...";
  ofile.open("greedy-report4.csv");
  for(int x = 0; x < A[0].size(); x++) {
    vector <int> C = changegreedy(V[0], A[0].at(x));
    ofile << A[0].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing greedy-report4.csv\n";
  //#5a
  cout << "Opening greedy-report5a.csv...";
  ofile.open("greedy-report5a.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changegreedy(V[1], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing greedy-report5a.csv\n";
  //#5b
  cout << "Opening greedy-report5b.csv...";
  ofile.open("greedy-report5b.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changegreedy(V[2], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing greedy-report5b.csv\n";
  //#6
  cout << "opening greedy-report6.csv...";
  ofile.open("greedy-report6.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changegreedy(V[3], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing greedy-report6.csv\n";
}

void dynamic(vector <vector <int> > &V, vector <vector <int> > &A)
{
  //#4
  ofstream ofile;
  cout << "Opening dp-report4.csv...";
  ofile.open("dp-report4.csv");
  for(int x = 0; x < A[0].size(); x++) {
    vector <int> C = changedp(V[0], A[0].at(x));
    ofile << A[0].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing dp-report4.csv\n";
  //#5a
  cout << "Opening dp-report5a.csv...";
  ofile.open("dp-report5a.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changedp(V[1], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing dp-report5a.csv\n";
  //#5b
  cout << "Opening dp-report5b.csv...";
  ofile.open("dp-report5b.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changedp(V[2], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing dp-report5b.csv\n";
  //#6
  cout << "opening dp-report6.csv...";
  ofile.open("dp-report6.csv");
  for(int x = 0; x < A[1].size(); x++) {
    vector <int> C = changedp(V[3], A[1].at(x));
    ofile << A[1].at(x) << "," << count(C) << "\n";
  }
  ofile.close();
  cout << "closing dp-report6.csv\n";
}
