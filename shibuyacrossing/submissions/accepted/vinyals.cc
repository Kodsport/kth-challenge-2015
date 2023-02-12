#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef vector<int> VI;

int lis(const VI& v) {
  set<int,greater<int>> s;
  for (int x : v) {
    auto it = s.upper_bound(x);
    if (it!=s.end()) s.erase(it);
    s.insert(x);
  }
  return s.size();
}

int main() {
  int N,M;
  cin >> N >> M;
  VI sigma(N);
  for (int i=0;i<N;++i) sigma[i]=i;
  for (int i=0;i<M;++i) {
    int a[2];
    cin >> a[0] >> a[1];
    sort(a,a+2);
    sigma[--a[0]]++;
    sigma[--a[1]]--;
  }
  VI sigmainv(N);
  for (int i=0;i<N;++i) sigmainv[sigma[i]]=i;
  cout << lis(sigmainv) << endl;
}
