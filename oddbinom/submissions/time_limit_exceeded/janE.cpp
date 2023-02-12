#include <iostream>
#include <algorithm>
using namespace std;
int main(){
	long long n; cin >> n;
	long long ans=0;
	for(long long i=0; i<n; i++){
		ans += 1LL<<__builtin_popcountll(i);
	}
	cout << ans << endl;
}
