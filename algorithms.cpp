#include "algorithms.h"

void printVector(const vector<int> &C){
	for(int i=0; i < C.size(); i++){
		cout << C[i] << " ";
	}
	cout << endl;
}
//Brute Force or Divede and Conquer Algorithm
vector<int> changeslow(const vector<int>& V, int A){
/*	cout << "vector V:" ;
	printVector(V);
	cout <<"\n Amount " << A << endl; 
        vector<vector<int> > visited(A);
	vector<int> C = slowhelper(V, A, &visited);
	printVector(C);*/
	vector<int> C(V.size(), 0);
	cout << "coins num " << slowhelper2(V, A) << endl;
	return C;

}

int count(const vector<int>& coins){
	int sum = 0;
	for(int i = 0; i < coins.size(); i++){
		sum += coins[i];
	}
	return sum;
}

vector<int> merge(const vector<int>& low, const vector<int>& high){
	vector<int> total(low.size(), 0);
	for(int i = 0; i < total.size(); i++){
		total[i] = low[i] + high[i];
	}
	return total;
}

vector<int> slowhelper(const vector<int>& V, int A, vector<vector<int> >* visited){
	//cout << "help " << A << endl;
	//int coins_num;
	vector<int> C(V.size(), 0);
	for(int i = 0; i < V.size(); i++){
		if(A == V[i]){
			//cout << "bingo" << endl;
			C[i] = 1;
			return C;
		}
	} 
	
	int min_sum = INT_MAX;
	for(int j = A - 1; j >= A/2; j--){
		vector<int> low;
		if (!(*visited)[A-j].empty()) {
			low = (*visited)[A-j];
		} else {
			low = slowhelper(V, A - j, visited); 
			(*visited)[A-j] = low;
		}

		vector<int> high;
                if (!(*visited)[j].empty()) {
                        high = (*visited)[j];
                } else {
                        high = slowhelper(V, j, visited);
                        (*visited)[j] = high;
                }
		int sum = count(low) + count(high);
		//cout << "sum = " << sum << endl;
		if(min_sum > sum){
			min_sum = sum;
			C = merge(low, high);
		}
	}
	return C;
}

int slowhelper2(const vector<int>& V, int A){
	for(int i = 0; i < V.size(); i++){
		if(A == V[i]){
			return 1;
		}
	}
	
	int min_sum = INT_MAX;
	for(int i = 0; i < V.size() && A > V[i]; i++){
		if(min_sum > slowhelper2(V, A- V[i])){
			min_sum = slowhelper2(V, A - V[i]);
		}
	}
	return min_sum + 1;
}

//Greedy Algorithm
vector<int> changegreedy(const vector<int>& V, int A){
  vector <int> C(V.size(), 0);
  while(A > 0)
    {
      for(int x = V.size()-1; x >= 0; x--)
	{
	  if(V.at(x) <= A) {
	    C.at(x) += 1;
	    A -= V.at(x);
	    break;
	  }
	}
    }
  printVector(C);
}

//Dynamic Programming Algorithm
vector<int> changedp(const vector<int>& V, int A){
  vector <int> T(1,0);
  int numCoins = dpHelper(V, T, 1, A);
  cout << "*" << numCoins << "*" << endl;
}

int dpHelper(const vector <int> &V, vector <int> &T, int n, int cents)
{
  int minCoins = n;
  int numCoins;
  for(int x = 0; x < V.size(); x++) {
    if(n == V.at(x)) {
      minCoins = 1;
      break;
    }
  }
  for(int i = 1; i < n; i++) {
    numCoins = T.at(i) + T.at(n - i);
    minCoins = min(minCoins, numCoins);
    if(i == n) {
      break;
    }
  }
  T.push_back(minCoins);
  if(n == cents) {
    return T.at(n);
  } else {
    return dpHelper(V, T, n + 1, cents);
  }
}

