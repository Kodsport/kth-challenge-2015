//Solution by lukasP (Lukáš Poláček)
//A DP solution is a bad idea for this problem
//I repeat, do not write a DP for this problem
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
#include <cassert>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int best[5001][5001][3][2]; // position, # of ATGs collected, shift, valid sequence
void impr(int &a, int b)
{
    a = min(a, b);
}
int main()
{
    int n;
    string s;
    cin >> n >> s;

    int m = s.size(), upper = min(m, n);
    rep(i,0,m+1) rep(j,0,upper+1) rep(k,0,3) rep(l,0,2)
        best[i][j][k][l] = n * 3;
    best[0][0][0][1] = 0;

    string q = "ATG";
    int res = n * 3 + 1;
    rep(i,0,m)
    {
        int iupper = min(upper, i + 1);
        rep(j,0,iupper+1) rep(kk,0,6) rep(l,0,2)
            if (best[i][j][kk % 3][l] < n * 3)
        {
            int k = kk % 3;
            if (!l && (k + i) % 3 > 0)
            {
                impr(best[i + 1][j][k][0], best[i][j][k][0]);
                impr(best[i][j][(k + 1) % 3][0], best[i][j][k][0] + 1);
            }
            else
            {
                if (q[(k + i) % 3] == s[i])
                    impr(best[i + 1][j + ((k + i) % 3 == 2)][k][1], best[i][j][k][l]);
                else
                {
                    impr(best[i][j + ((k + i) % 3 == 2)][(k + 1) % 3][1], best[i][j][k][l] + 1);
                    impr(best[i + 1][j][k][0], best[i][j][k][l]);
                }
            }
        }
    }

    rep(i,0,m+1) rep(j,0,upper+1) rep(k,0,3)
        res = min(res, best[i][j][k][1] + 3 * (n - j));

    cout << res << endl;
}
