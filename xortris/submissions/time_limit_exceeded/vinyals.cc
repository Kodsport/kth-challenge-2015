#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <cstring>
#include <bitset>
#include <stack>
using namespace std;
typedef set<int> SI;
typedef vector<int> VI;
typedef vector<VI> VVI;

int m,n;
int nseen;
char seen[1<<25];
SI edges;

int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

void addedge(const VVI& board) {
  int mask=0;
  for (const VI& v : board) {
    for (int x : v) {
      mask<<=1;
      mask|=x;
    }
  }
  edges.insert(mask);
}

void mknotT(int ii, int jj, int kk) {
  VVI board(m,VI(n));
  board[ii][jj]=1;
  for (int d=0;d<3;++d) {
    ii+=dx[kk&3];
    jj+=dy[kk&3];
    kk>>=2;
    if (ii<0||ii>=m||jj<0||jj>=n||board[ii][jj]) return;
    board[ii][jj]=1;
  }
  addedge(board);
}

void mkT(int i, int j, int kk) {
  VVI board(m,VI(n));
  board[i][j]=1;
  for (int d=0;d<3;++d) {
    int ii=i+dx[kk&3];
    int jj=j+dy[kk&3];
    kk>>=2;
    if (ii<0||ii>=m||jj<0||jj>=n||board[ii][jj]) return;
    board[ii][jj]=1;
  }
  addedge(board);
}

void mkedges() {
  for (int i=0;i<m;++i) {
    for (int j=0;j<n;++j) {
      for (int k=0;k<2<<6;++k) {
        mknotT(i,j,k);
        mkT(i,j,k);
      }
    }
  }
}

bool dfs(int x) {
  stack<int> s;
  s.push(x);
  seen[x]=true;
  while(not s.empty()) {
    x=s.top();s.pop();
    if (x==0) return true;
    for (int y : edges) {
      int xx=x^y;
      if (seen[xx]) continue;
      s.push(xx);
      seen[xx]=true;
    }
  }
  return false;
}

int getboard() {
  int mask=0;
  for (int i=0;i<m;++i) {
    string s;
    cin >> s;
    for (char c : s) {
      mask<<=1;
      if (c=='X') mask|=1;
    }
  }
  return mask;
}

int main() {
  memset(seen,0,sizeof(seen));
  nseen=0;
  cin >> m >> n;
  mkedges();
  cerr << edges.size() << endl;
  //for (int e : edges) cerr << "  " << bitset<4>(e) << endl;
  cout << (dfs(getboard())?"possible":"impossible") << endl;
}
