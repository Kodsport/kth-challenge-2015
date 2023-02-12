
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

typedef vector<int> vi;
vector<vector<string>> p = {{"XX", "XX"}, {"XXXX"}, {"XX.", ".XX"}, {"XXX", ".X."}, {"XXX", "..X"}};
vector<string> rotate(vector<string> a)
{
    int n = a.size(), m = a[0].size();
    vector<string> res(m, string(n, 'X'));
    rep(i,0,n) rep(j,0,m)
        res[m - 1 - j][i] = a[i][j];
    return res;
}
vector<string> flip(vector<string> a)
{
    vector<string> res = a;
    rep(i,0,a.size() / 2)
        swap(res[i], res[a.size() - 1 - i]);
    return res;
}
int n, m;
int code(int a, int b)
{
    return a * m + b;
}
bitset<190000> t[10000];
bitset<1000> g[1000];
int main()
{
    scanf("%d %d", &n, &m);

    int cnt = 0;
    rep(i,0,n)
    {
        string s; cin >> s;
        replace(s.begin(), s.end(), 'X', '1');
        replace(s.begin(), s.end(), '.', '0');
        g[i] = bitset<1000> (s);
        cnt += g[i].count();
    }
    rep(i,0,n) rep(j,0,m)
        t[code(i, j)].reset();

    set<vector<string>> all;
    for (vector<string> w : p)
    {
        rep(i,0,4)
        {
            all.insert(w);
            w = rotate(w);
        }
    }
    for (vector<string> w : all)
        all.insert(flip(w));

    vector<vector<string>> piece(all.begin(), all.end());
    int cur = 0;
    rep(k,0,piece.size())
    {
        vector<string> &a = piece[k];
        rep(i,0,n) rep(j,0,m)
            if (a.size() + i <= (size_t)n && a[0].size() + j <= (size_t)m)
            {
                rep(l,0,a.size()) rep(o,0,a[0].size())
                    if (a[l][o] == 'X')
                        t[code(i + l, j + o)][cur] = true;
                cur++;
            }
    }

    rep(i,0,n) rep(j,0,m)
        t[code(i, j)][cur] = g[i][j];

    int rank = 0;
    vi lead(n * m, -1);
    rep(l,0,cur)
    {
        rep(i,rank,lead.size())
            if (t[i][l])
            {
                swap(t[i], t[rank]);
                break;
            }

        if (!t[rank][l]) continue;

        rep(i,0,lead.size()) if ((int)i != rank && t[i][l])
            t[i] ^= t[rank];
        lead[rank] = l;
        rank++;
    }

    rep(l,rank,lead.size())
    {
        if (t[l].count())
        {
            printf("impossible\n");
            return 0;
        }
    }
    printf("possible\n");
}
