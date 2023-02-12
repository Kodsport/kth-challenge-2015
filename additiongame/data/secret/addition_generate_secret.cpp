#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> uniform(int n, bool stupid) {
	vector<int> a(n, 0);
	for(int i = 0; i < n; ++i) a[i] = rand() % n;
	
	int s = 0;
	for(int i = 0; i < n-1; ++i) s = (s + a[i]) % n;
	a[n-1] = (n-s)%n;
	if(stupid) a[n-1] = (a[n-1] + 1+rand()%(n-1))%n;
	return a;
}

vector<int> permutation(int n) {
	vector<int> a(n, 0);
	for(int i = 0; i < n; ++i) {
		int j = rand()%(i+1);
		a[i] = a[j];
		a[j] = i;
	}
	return a;
}

// Generate sequence using only k different values,
// with sum zero. (Not uniform.)
vector<int> almost_constant(int n, int k) {
	set<int> S; while(S.size() < k - 1) S.insert(rand()%n);
	vector<int> L(S.begin(), S.end());
	vector<int> a(n);
	int s = 0;
	for(int i = 0; i < n-1; ++i) {
		a[i] = L[rand()%(k-1)];
		s = (s + a[i]) % n;
	}
	a[n-1] = (n-s)%n;
	random_shuffle(a.begin(), a.end());
	return a;
}


int main(int argc, char**argv) {
	srand(744);
	int n = 5, k = 2;
	if(argc > 1) n = atoi(argv[1]);
	if(argc > 2) k = atoi(argv[2]);

	vector<int> a = almost_constant(n, k);//uniform(n, stupid);
	cout << n << endl;
	for(int i = 0; i < n; ++i) 
		cout << (1+a[i]) << ' ';
	cout << endl;

	return 0;
}
