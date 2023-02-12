#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> vi;

int main() {
    int n;
    string s;
    cin >> n >> s;
    int L = s.length();
    s.append("XXX");
    //M[i][j] is the largest number of methionines obtainable from
    //s[i:end] adding j letters
    vector<vi> M(L+3, vi(2*L+1, 0));
    for (int j = 0; j < 2*L+1; ++j) {
        for (int i = L-1; i >= 0; --i) {
            if (s.compare(i, 3, "ATG") == 0)
                M[i][j] = M[i+3][j] + 1;
            else
                M[i][j] = M[i+3][j];
            if (j < 1) 
                continue;
            if (s.compare(i, 2, "AT") == 0 || 
                s.compare(i, 2, "AG") == 0 ||
                s.compare(i, 2, "TG") == 0)
                M[i][j] = max(M[i][j], M[i+2][j-1] + 1);
            else
                M[i][j] = max(M[i][j], M[i+2][j-1]);
            if (j < 2)
                continue;
            if (s.compare(i, 1, "A") == 0 || 
                s.compare(i, 1, "T") == 0 ||
                s.compare(i, 1, "G") == 0)
                M[i][j] = max(M[i][j], M[i+1][j-2] + 1);
            else
                M[i][j] = max(M[i][j], M[i+1][j-2]);
            if (j < 3)
                continue;
            M[i][j] = max(M[i][j], M[i][j-3]+1);
        }
        if (M[0][j] >= n) {
            cout << j << endl;
            return 0;
        }
    }
    cout << min(min((n-M[0][2*L])*3+2*L, (n-M[0][2*L-1])*3+2*L-1),
       (n-M[0][2*L-2])*3+2*L-2) << endl;
}