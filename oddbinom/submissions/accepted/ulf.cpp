#include <iostream>
#include <cmath>
using namespace std;

long long n;
long long rec(int pos, long long p3) {
    if (pos < 0)
        return 0;
    if (n & (1LL << pos))
        return 2*rec(pos-1, p3 / 3) + p3;
    return rec(pos-1, p3 / 3);
}

int main() {
    cin >> n;
    long long p3 = 1;
    for (int i = 0; i < 38; i++)
        p3 *= 3;
    cout << rec(38, p3) << endl;
}
