//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
int main()
{
    int n, m; scanf("%d %d", &n, &m);

    vi pos(n);
    rep(i,0,n) pos[i] = i;

    rep(i,0,m)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        if (a > b)
            swap(a, b);
        pos[a]++;
        pos[b]--;
    }

    vi best(n, 1);
    rep(i,1,n)
        rep(j,0,i) if (pos[j] > pos[i])
            best[i] = max(best[i], best[j] + 1);

    cout << *max_element(best.begin(), best.end()) << endl;
}
