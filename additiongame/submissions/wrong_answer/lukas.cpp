//Solution by lukasP (Lukáš Poláček)
//Implementation of "A Combinatorial Problem on Abelian Groups" by Marshall Hall, Jr.
#include <iostream>
#include <vector>
#include <set>
#include <numeric>

#include <cstdio>
#include <cassert>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
int n;
vi a, b, c, pb, ipb;
void print(vi v, vi ipb)
{
    rep(ii,0,n)
    {
        int i = ipb[ii];
        cout << (v[i] == 0 ? n : v[i]) << (ii + 1 < n ? " " : "\n");
    }
}
void fix(int j, int nj)
{
    rep(k,0,n)
    {
        set<int> w = {c[j], c[nj]};
        int alt1 = (j + b[j]) % n;
        int alt2 = (j + b[nj]) % n;
        if (w.count(alt1) || w.count(alt2))
        {
            int res = w.count(alt1) ? alt1 : alt2;
            if (res == alt2)
            {
                swap(b[j], b[nj]);
                swap(pb[j], pb[nj]);
            }
            if (c[nj] == res)
                swap(c[j], c[nj]);
            return;
        }

        int sol = (n + c[j] - b[j]) % n;
        swap(b[j], b[sol]);
        swap(pb[j], pb[sol]);
        swap(c[j], c[sol]);
        swap(c[j], c[nj]);
    }
}
int main()
{
    scanf("%d", &n);
    a.resize(n); b.resize(n); c.resize(n);
    pb.resize(n); ipb.resize(n);

    rep(i,0,n)
    {
        a[i] = c[i] = pb[i] = i;
        scanf("%d", &b[i]);
    }

    if (accumulate(b.begin(), b.end(), 0) % n != 0)
    {
        cout << "impossible" << endl;
        return 0;
    }

    rep(i,0,n - 1)
        fix(i, i + 1);

    rep(j,0,n) ipb[pb[j]] = j;
    rep(j,0,n) a[j] = (n - a[j]) % n;

    print(a, ipb);
    print(c, ipb);
}
