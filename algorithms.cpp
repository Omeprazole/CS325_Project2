/******************************************************************************
Use three algorithms to slove the coin change problem
******************************************************************************/
#include "algorithms.h"

/*
 * Count total coins needed with the coin number of each dominations
 */
int count(const vector<int>& coins){
	int sum = 0;
	for (int i = 0; i < coins.size(); i++){
		sum += coins[i];
	}
	return sum;
}

/*
 * Help changeslow function, conquer two divided vectors
 */
vector<int> merge(const vector<int>& low, const vector<int>& high){
	vector<int> total(low.size(), 0);
	for (int i = 0; i < total.size(); i++){
		total[i] = low[i] + high[i];
	}
	return total;
}


/*
 * Brute Force or Divede and Conquer Algorithm
 * Recursively find the correponding coin number of each denominations
 */
vector<int> changeslow(const vector<int>& V, int A){
	//Declare a vector to store the correponding coin number 
	//of each denominations. Initialize each element to 0.
	vector<int> C(V.size(), 0);
	//Base case
	for (int i = 0; i < V.size(); i++){
		if (A == V[i]){
			C[i] = 1;
			return C;
		}
	}

	//Define a variable to hold the minimum sum
	//Initialize it to max int
	int min_sum = INT_MAX;

	//Recursive case
	for (int i = A - 1; i >= A / 2; i--){
		vector<int> low, high;

		//Find the minimum number of coins needed to make A-i cents
		low = changeslow(V, A - i);

		//Find the minimum number of coins needed to make i cents
		high = changeslow(V, i);

		//Choose the i that minimizes this sum
		int sum = count(low) + count(high);
		if (min_sum > sum){
			min_sum = sum;
			C = merge(low, high);
		}

	}
	return C;
}

//Greedy Algorithm
vector<int> changegreedy(const vector<int>& V, int A){
	vector <int> C(V.size(), 0);
	while (A > 0)
	{
		for (int x = V.size() - 1; x >= 0; x--)
		{
			if (V.at(x) <= A) {
				C.at(x) += 1;
				A -= V.at(x);
				break;
			}
		}
	}

	return C;

}

//Dynamic Programming Algorithm
vector<int> changedp(const vector<int>& V, int A){
	//Define a vector to hold the coin number of each coin value
	vector<int> C(V.size(), 0);

	//Define a two dimentional array(table) to memory the minimum coin number
	//of each amount of money from 0 to A
	int T[V.size()][A + 1];

	//Initialize the first column of the table to 0
	for (int i = 0; i < V.size(); i++){
		T[i][0] = 0;
	}

	//Initialize the first row of table
	for (int j = 1; j <= A; j++){
		T[0][j] = j;
	}

	//Calculate each minimum number
	for (int i = 1; i < V.size(); i++){
		for (int j = 1; j <= A; j++){
			if (j >= V[i]){
				T[i][j] = min(T[i - 1][j], T[i][j - V[i]] + 1);
			}
			else {
				T[i][j] = T[i - 1][j];
			}

		}
	}
	cout << "";
	//Track to find the number of coins on each coin value
	int i = V.size() - 1;
	int j = A;
	int track = T[V.size() - 1][A];
	while (j > 0 && i > 0){
		if (T[i - 1][j] == track)
			i--;
		else{
			track--;
			C[i]++;
			j = j - V[i];
		}

	}
	//return result
	return C;
}














