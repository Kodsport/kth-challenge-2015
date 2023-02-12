//Solution by Erik Aas
#include <algorithm>
#include <iostream>
using namespace std;

int pi[800+10], row[800+10];
int N,M,L;

// Use Robinson-Schensted insertion!

int main() {
	cin >> N >> M;
	for(int i = 0; i < N; ++i) pi[i] = i;
	for(int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		pi[--a]++; pi[--b]--;	
	}
	reverse(pi, pi + N);
	L = 0;
	for(int i = 0; i < N; ++i) {
		int k = 0;
		while(k < L && pi[i] > row[k]) ++k;
		if(k == L) ++L;
		row[k] = pi[i];
	}
	cout << L << endl;
}
