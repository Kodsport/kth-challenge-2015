//Solution by lukasP (Lukáš Poláček)
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cassert>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
int main()
{
    int n;
    scanf("%d", &n);
    vector<multiset<int> > g(n);
    vi p(n);
    rep(i,0,n)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        g[a].insert(b);
        g[b].insert(a);
    }

    queue<int> q;
    rep(i,0,n) if (g[i].size() == 1)
        q.push(i);

    for (; !q.empty(); q.pop())
    {
        int u = q.front(), v = *g[u].begin();
        g[v].erase(g[v].find(u)); g[u].erase(g[u].find(v));
        if (g[v].size() == 1)
            q.push(v);
    }

    rep(k,0,n) if (g[k].size() == 2)
    {
        int u = *g[k].begin(), v = k;
        g[v].erase(g[v].find(u)); g[u].erase(g[u].find(v));
        while (u != k)
        {
            v = u; u = *g[u].begin();
            g[v].erase(g[v].find(u)); g[u].erase(g[u].find(v));
        }
    }
    rep(k,0,n)
        assert(g[k].empty());

    return 42;
}
