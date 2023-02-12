#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

bool hasclique(const VVI& g, int k) {
  int n=g.size();
  VI v(n);
  for (int i=n-k;i<n;++i) v[i]=1;
  do {
    bool ook=true;
    for (int i=0;ook and i<n;++i) {
      if (not v[i]) continue;
      for (int j=i+1;ook and j<n;++j) {
        if (not v[j]) continue;
        ook&=g[i][j];
      }
    }
    if (ook) return true;
  }
  while(next_permutation(v.begin(), v.end()));
  return false;
}

int maxclique(const VVI& g) {
  int n=g.size();
  for (int i=1;i<=n;++i) {
    if (not hasclique(g,i)) return i-1;
  }
  return n;
}

int main() {
  int N,M;
  cin >> N >> M;
  VVI g(N,VI(N));
  for (int i=0;i<M;++i) {
    int a,b;
    cin >> a >> b;
    --a;--b;
    g[a][b]=g[b][a]=1;
  }
  cout << maxclique(g) << endl;
}
