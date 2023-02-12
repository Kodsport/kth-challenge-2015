#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> m(n-1);
    for (int i = 0; i < n-1; ++i) {
        cin >> m[i];
    }
    double res = 0;
    int req = 1;
    double side = pow(2, -3.0/4);
    for (int i = 0; req > 0 && i < n-1; ++i) {
        res += req * side;
        req *= 2;
        req -= m[i];
        side /= sqrt(2);
    }

    cout.precision(6);
    if (req > 0)
        cout << "impossible" << endl;
    else
        cout << fixed << res << endl;
}
