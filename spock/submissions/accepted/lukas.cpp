//Solution by lukasP (Lukáš Poláček)
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

string val[] = {"rock", "paper", "scissors", "lizard", "Spock"};
string pic[] = {"scissors", "paper", "rock", "lizard", "Spock"};

int p = 127;
int inv[127];
struct Mod {
    int x;
    Mod(int xx) : x(xx) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % p); }
    Mod operator-(Mod b) { return Mod((x - b.x + p) % p); }
    Mod operator*(Mod b) { return Mod((x * b.x) % p); }
    Mod operator/(Mod b) {
        return Mod(x * inv[b.x] % p);
    }
};

int advance(Mod& a, Mod& b, Mod x, vi& moves)
{
    for (int m : moves)
    {
        if (m != x.x % 5)
            return -1;
        x = x * a + b;
    }
    return x.x;
}

int main()
{
    bool g[5][5];
    memset(g, 0x00, sizeof(g));

    inv[0] = 0;
    rep(i,1,p)
        rep(j,1,p) if (i * j % p == 1)
            inv[i] = j;

    map<string, int> invmoves;
    rep(i,0,5)
        invmoves[val[i]] = i;

    int win[5];
    rep(i,0,5)
        win[invmoves[pic[i]]] = invmoves[pic[(i + 4) % 5]];

    int r;
    scanf("%d", &r);

    int plays = 10;
    vector<int> moves;
    rep(i,0,plays)
    {
        cout << val[rand() % 5] << endl;
        string move;
        cin >> move;
        moves.push_back(invmoves[move]);
    }

    bool same = true;
    rep(i,1,moves.size())
        if (moves[i] != moves[0])
            same = false;

    vector<array<Mod, 3> > cand;
    for (int s1 = moves[0]; s1 < p; s1 += 5)
        for (int s2 = moves[1]; s2 < p; s2 += 5)
            if (s2 != s1)
        {
            Mod m1(s1), m2(s2);
            for (int s3 = moves[2]; s3 < p; s3 += 5)
                if (s3 != s2)
            {

                Mod m3(s3);
                Mod a = (m3 - m2) / (m2 - m1);
                Mod b = m2 - m1 * a;
                int res = advance(a, b, m1, moves);
                if (res >= 0)
                    cand.push_back(array<Mod, 3>{a, b, res});
            }
        }

    if (same)
        cand.push_back(array<Mod, 3>{Mod(0), Mod(moves[0]), Mod(moves[0])});

    rep(i,plays,r)
    {
        assert(cand.size() >= 1);
        cout << val[win[cand[0][2].x % 5]] << endl;
        string move;
        cin >> move;

        int mod = invmoves[move];
        vector<array<Mod, 3> > ncand;
        for (auto w : cand)
            if (w[2].x % 5 == mod)
                ncand.push_back(w);
        cand = ncand;
        for (auto& w : cand)
            w[2] = (w[2] * w[0] + w[1]);
    }
}
