#include <iostream>
using namespace std;

bool solve1(__int128 board, int n) {
  if (n<=3) return board==0;
  if (board&1) return solve1((board^0xf)>>1,n-1);
  return solve1(board>>1,n-1);
}

bool solve1(const string& board) {
  int n=board.size();
  __int128 boardint=0;
  for (char c:board) {
    boardint<<=1;
    if (c=='X') boardint|=1;
  }
  return solve1(boardint,n);
}

bool solve() {
  int m,n;
  cin >> m >> n;
  string board;
  if (m==1) {
    cin >> board;
    return solve1(board);
  }
  else if (n==1) {
    board.resize(m);
    for (int i=0;i<m;++i) cin >> board[i];
    return solve1(board);
  }
  else {
    int count=0;
    for (int i=0;i<m;++i) {
      for (int j=0;j<n;++j) {
        char c;
        cin >> c;
        count += (c=='X'?1:0);
      }
    }
    if (n==2 and m==2) return !(count&3);
    return !(count&1);
  }
}

int main() {
  cout << (solve()?"possible":"impossible") << endl;
}
