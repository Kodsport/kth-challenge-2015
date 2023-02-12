#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
typedef vector<int> vi;
int n;

ostream& operator<<(ostream& os, const vi& v) {
	rep(i,0,v.size())
		os << v[i] << ' ';
	return os;
}

vi diff(vi a, vi b) {
	vi c(n);	rep(i,0,n) c[i] = (n+a[i]-b[i])%n;
	return c;
}

int main() {
	cin >> n;
	vi a(n); rep(i,0,n) {cin >> a[i];a[i]%=n;}
	int s = 0; rep(i,0,n) s = (s + a[i]) % n;
	if(s != 0) {
		cout << "impossible" << endl;
		return 0;
	}
	vi pi(n); rep(i,0,n) pi[i]=i;
	vi pi_inv(pi);
	while(true) {
		vi P = diff(a,pi);
		vi f(n,0); rep(i,0,n) f[P[i]]++;
		vi many, few;
		rep(i,0,n) {
			if(f[P[i]] > 1) many.push_back(i);
			if(f[i]==0) few.push_back(i);
		}
		if(many.size() == 0 || few.size() == 0) {
			break;
		}
		int i = many[rand()%many.size()], k = few[rand()%few.size()], g = (n+a[i]-pi[i])%n, pip = (g-k+pi[i]+n)%n;
		int j = pi_inv[pip];
		swap(pi_inv[pi[i]], pi_inv[pi[j]]);
		swap(pi[i], pi[j]);

	}
	vi sigma = diff(a,pi);
	rep(i,0,n) {if(pi[i]==0) pi[i]=n; if(sigma[i]==0) sigma[i]=n;}
	cout << pi << endl << sigma << endl;

	return 0;
}
