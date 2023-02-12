#include <iostream>
#include <cmath>
using namespace std;

int n;
long long rec(int pos) {
    if (pos < 0)
        return 0;
    if (n & (1 << pos))
        return 2*rec(pos-1) + pow(3ll, pos);
    return rec(pos-1);
}

int main() {
    cin >> n;
    cout << rec(31) << endl;
}