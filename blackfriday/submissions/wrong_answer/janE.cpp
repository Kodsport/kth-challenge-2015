#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main() {
	int n; cin >> n;
	map<int,vector<int> >M;
	for(int i=1; i<=n; i++){
		int x; cin >> x;
		M[x].push_back(i);
	}
	for(int v=6; v>=1; v--) if ((int)M[v].size() >= 1) {
		cout << M[v][0] << endl;
		return 0;
	}
	cout << "none" << endl;
}
