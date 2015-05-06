#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;
void printVector(const vector<int> &C);

//Brute Force or Divde and Conquer Algorithm
vector<int> changeslow(const vector<int>& V, int A);
vector<int> slowhelper(const vector<int>& V, int A, vector<vector<int> >* visited);
int count(const vector<int>& coins);
vector<int> merge(const vector<int>& low, const vector<int>& high);

//Greedy Algorithm
vector<int> changegreedy(const vector<int>& V, int A);

//Dynamic Programming Algorithm
vector<int> changedp(const vector<int>& V, int A);

#endif
