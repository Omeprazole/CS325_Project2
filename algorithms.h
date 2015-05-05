#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

//Brute Force or Divede and Conquer Algorithm
vector<int> changeslow(const vector<int>& v, int A);

//Greedy Algorithm
vector<int> changegreedy(const vector<int>& v, int A);

//Dynamic Programming Algorithm
vector<int> changedp(const vector<int>& v, int A);

#endif
