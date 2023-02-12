#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
typedef vector<int> vi;

vi bb(string s) {
	vi rt; istringstream is(s);
	int x;while(is>>x) rt.push_back(x);
	return rt;
}

ostream& operator<<(ostream& os, const vi& v) {
	rep(i,0,v.size())
		os << v[i] << ' ';
	return os;
}

int n;

inline int _(int a, int b) { return (a-b+n)%n; }

// The numbers i-A[i] are distinct for i != l1, l2.
// The two numbers missing from {0,1,...,n-1} among these are m1 and m2.
// Make them all distinct by permuting A.
void fix(const vi& a, vi&p, vi&p_inv, int l1, int l2, int m1, int m2) {
	while(1) {
		if(_(a[l1], p[l1]) == m1 or _(a[l1], p[l1]) == m2) return;
		int k = p_inv[_(a[l1], m1)];
		m1 = _(a[k],p[k]);
		swap(m1,m2);
		swap(p[k], p[l1]);
		swap(p_inv[p[k]], p_inv[p[l1]]);
		l1 = k;	
	}
}

vi solve(const vi& a) {
	n = a.size();
	vi cur(n, 0);
	vi p(n); rep(i,0,n) p[i]=i;
	vi p_inv(p);
	int l1,l2=n-1,m1,m2;
	rep(i,0,n-1) {
		if(cur[i] != a[i]) {
			l1 = i;
			m1 = _(cur[l1],p[l1]), m2 = _(cur[l2], p[l2]);
			cur[l2] = (cur[l1] + cur[l2] - a[l1] + n)%n;
			cur[l1] = a[l1];
			fix(cur, p, p_inv, l1, l2, m1, m2);
		}
	}
	return p;
}

int main() {
	cin >> n;
	vi a(n); rep(i,0,n) {cin >> a[i]; a[i] %= n;}
	int s = 0; rep(i,0,n) s = (s + a[i]) % n;
	if(s != 0) {
		cout << "impossible" << endl;
		return 0;
	}
	vi p = solve(a);
	vi q; rep(i,0,n) q.push_back(_(a[i],p[i]));
	rep(i,0,n) {if(p[i]==0)p[i]=n;if(q[i]==0)q[i]=n;}
	cout << p << endl;
	cout << q << endl;
	return 0;
}
