#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

int main() {
  int n;
  cin >> n;
  VI winner(7);
  for (int i=0;i<n;++i) {
    int x;
    cin >> x;
    int& w=winner[x];
    if (w>0) w=-1;
    else if (w==0) w=i;
  }
  for (int i=6;i>=1;--i) {
    if (winner[i]>0) {
      cout << winner[i]+1 << endl;
      return 0;
    }
  }
  cout << "none" << endl;
}
