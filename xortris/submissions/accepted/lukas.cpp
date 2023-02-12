
//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int n, m;
bool solve(bitset<1000> b)
{
    for (int i = m - 1; i >= 3; i--) if (b[i])
        rep(j,0,4)
            b[i - j].flip();
    return (b.to_ulong() == 0);
}
int main()
{
    scanf("%d %d", &n, &m);

    bitset<1000> g[1000];
    int cnt = 0;
    rep(i,0,n)
    {
        string s; cin >> s;
        replace(s.begin(), s.end(), 'X', '1');
        replace(s.begin(), s.end(), '.', '0');
        g[i] = bitset<1000> (s);
        cnt += g[i].count();
    }

    bool res;

    if (n == 1 || m == 1)
    {
        bitset<1000> b = g[0];
        if (m == 1)
        {
            rep(i,0,n) b[i] = g[i][0];
            swap(n, m);
        }
        res = solve(b);
    }
    else
    {
        if (m == 2 && n == 2)
            res = cnt % 4 == 0;
        else
            res = cnt % 2 == 0;
    }

    cout << (!res ? "im" : "") << "possible" << endl;
}
