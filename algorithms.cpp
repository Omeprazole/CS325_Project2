#include "algorithms.h"

void printVector(const vector<int> &C){
	for(int i=0; i < C.size(); i++){
		cout << C[i] << " ";
	}
	cout << endl;
}
//Brute Force or Divede and Conquer Algorithm
vector<int> changeslow(const vector<int>& V, int A){
	cout << "vector V:" ;
	printVector(V);
	cout <<"\n Amount " << A << endl; 
        vector<vector<int> > visited(A);
	vector<int> C = slowhelper(V, A, &visited);
	printVector(C);
	cout << "conins num" << count(C) << endl;
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
//Greedy Algorithm
vector<int> changegreedy(const vector<int>& V, int A){

}

//Dynamic Programming Algorithm
vector<int> changedp(const vector<int>& V, int A){

}
