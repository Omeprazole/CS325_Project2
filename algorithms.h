#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

//Untility funcitons
void printVector(const vector<int> &C);

//Count total number in a vector
int count(const vector<int>& coins);


//Brute Force or Divde and Conquer Algorithm
vector<int> changeslow(const vector<int>& V, int A);
//Help changeslow funciton to merge two vectors
vector<int> merge(const vector<int>& low, const vector<int>& high);

//Greedy Algorithm
vector<int> changegreedy(const vector<int>& V, int A);

//Dynamic Programming Algorithm
vector<int> changedp(const vector<int>& V, int A);
int dpHelper(const vector <int> &V, vector <int> &T, int n, int cents);

#endif
