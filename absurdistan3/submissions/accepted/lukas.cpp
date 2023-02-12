//Solution by lukasP (Lukáš Poláček)
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int main()
{
    int n;
    scanf("%d", &n);
    vector<multiset<int> > g(n);
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
        printf("%d %d\n", u + 1, v + 1);
        g[v].erase(g[v].find(u)); g[u].erase(g[u].find(v));
        if (g[v].size() == 1)
            q.push(v);
    }

    rep(k,0,n) if (g[k].size() == 2)
    {
        int u = *g[k].begin(), v = k;
        g[v].erase(g[v].find(u)); g[u].erase(g[u].find(v));
        printf("%d %d\n", u + 1, v + 1);
        while (u != k)
        {
            v = u; u = *g[u].begin();
            g[v].erase(g[v].find(u)); g[u].erase(g[u].find(v));
            printf("%d %d\n", u + 1, v + 1);
        }
    }
}
