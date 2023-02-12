#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

typedef vector<int> VI;
typedef unordered_multiset<int> HI;
typedef vector<HI> VHI;
typedef queue<int> QI;

int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  VHI g(n);
  for (int i=0;i<n;++i) {
    int a,b;
    cin >> a >> b;
    --a;--b;
    g[a].insert(b);
    g[b].insert(a);
  }
  VI seen(n,false);
  QI deg1;
  for (int i=0;i<n;++i) if (g[i].size()==1) deg1.push(i);
  while (not deg1.empty()) {
    int u=deg1.front();deg1.pop();
    int v=*g[u].begin();
    seen[u]=true;
    cout << u+1 << ' ' << v+1 << endl;
    g[u].clear();
    g[v].erase(g[v].find(u));
    if (g[v].size()==1) deg1.push(v);
  }
  for (int i=0;i<n;++i) {
    int u=i;
    while(not seen[u]) {
      int v=*g[u].begin();
      seen[u]=true;
      cout << u+1 << ' ' << v+1 << endl;
      g[u].erase(g[u].find(v));
      g[v].erase(g[v].find(u));
      u=v;
    }
  }
}
