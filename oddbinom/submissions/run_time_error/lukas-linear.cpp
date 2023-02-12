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
    int n; scanf("%d", &n);
    n--;
    vector<ll> c(n + 1);

    c[0] = 0;
    rep(i,1,n+1)
    {
        if (i & 1)
            c[i] = 2 * c[i / 2];
        else
            c[i] = i / 2 + c[i / 2];
    }

    cout << (n + 1) * ll(n + 2) / 2 - accumulate(c.begin(), c.end(), 0LL) << endl;
}
