#include <iostream>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define trav(it,v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
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

void Erase(vi&l, int e) {
	int k = 0;
	while(k < l.size() && l[k] != e) ++k;
	while(k < l.size()-1) {l[k] = l[k+1];++k;}
	l.pop_back();
}

void Insert(vi&l, int e) {
	l.push_back(e);
}

int main() {
	srand(time(0));
	cin >> n;
	vi a(n); rep(i,0,n) {cin >> a[i]; a[i] %= n; }
	int s = 0; rep(i,0,n) s = (s + a[i]) % n;
	if(s != 0) {
		cout << "impossible" << endl;
		return 0;
	}
	vi pi(n); rep(i,0,n) pi[i]=i;
	vi pi_inv(pi);
	vi freq(n,0);
	vi P = diff(a,pi);
	rep(i,0,n) freq[P[i]]++;
	vi many(n,0);
	set<int> few;
	vector<vector<int> > invers(n);
	rep(i,0,n) invers[P[i]].push_back(i);
	rep(i,0,n) {if(invers[i].size() > 1) many[i]=1; else if(invers[i].size() == 0) few.insert(i);}


//	int n_it = 0;
	while(1) {
		
		/*
 * 	Find overrepresented value k.
 * 	Take an element i equal to p[i] = k.
 *	Let l be an underrepresented value, find j such that a[i]-p[j] = l,
 *	Swap pi[i] and pi[j]
 *	SO: i and j swap. k disappears, l appears at i. At j, a[j]-pi[j] disappears, a[j]-pi[i] appears.
 *	These are called d1,i1,d2,i2.
 */	

		int k = rand()%n; 
		int T = 0; while(T < n && !many[(k+T)%n]) ++T;if(T == n) {break;}
		k = (k + T) %n;
		int i = invers[k][rand()%(invers[k].size())];
		
		int l, j;
		l = *lower_bound(few.begin(), few.end(), rand()%(*(--few.end())));
		j = pi_inv[(n+a[i]-l)%n];

/*
		cout << endl;
		cout << "a : " << a << endl << "pi: " << pi << endl << "P : " << P << endl;
		for(int i = 0; i< n;++i)
			cout << "invers["<<i<<"]:" << invers[i] << endl;
*/
		//
		//decrease
		int d1 = (a[i]-pi[i]+n)%n, d2 = (a[j]-pi[j]+n)%n;
		//increase
		int i1 = (a[i]-pi[j]+n)%n, i2 = (a[j]-pi[i]+n)%n;
/*
		cout << "chose k = " << k << ", l = " << l << endl;
		cout << "will swap " << i << " and " << j << endl;
		cout << d1 << " , " << d2 << " ; " << i1 << " , " << i2 << endl;
*/
		P[i] = (a[i] - pi[j] + n) % n;
		P[j] = (a[j] - pi[i] + n) % n;

		Erase(invers[d1], i);
		Erase(invers[d2], j);
		Insert(invers[i1], i);
		Insert(invers[i2], j);

		if(invers[i1].size() > 1) many[i1] = 1;
		if(invers[i2].size() > 1) many[i2] = 1;
		if(invers[d1].size() <=1) many[d1] = 0;
		if(invers[d2].size() <=1) many[d2] = 0;
		
		if(invers[i1].size() >= 1) few.erase(i1);
		if(invers[i2].size() >= 1) few.erase(i2);
		if(invers[d1].size() == 0) few.insert(d1);
		if(invers[d2].size() == 0) few.insert(d2);
		
		swap(pi[i], pi[j]);
		swap(pi_inv[pi[i]], pi_inv[pi[j]]);
//		++n_it;
	}
	
	rep(i,0,n) {if(pi[i] == 0) pi[i] = n; if(P[i] == 0) P[i] = n;}
	cout << pi << endl << P << endl;


//	cout << n_it << " iterations"<<endl;

	return 0;
}
