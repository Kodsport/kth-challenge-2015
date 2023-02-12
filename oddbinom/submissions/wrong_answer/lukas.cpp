//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int main()
{
    ll n; scanf("%lld", &n);

    bitset<37> b(n);
    ll res = 0;
    int cnt = b.count();
    for (ll i = 0, p3 = 1; i < 36; i++, p3 *= 3)
        if (b[i])
        res += (1LL << --cnt) * p3;
    cout << res << endl;
}
