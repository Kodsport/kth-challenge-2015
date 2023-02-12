#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

typedef vector<int> vi;

const int N = 5;
const int p = 127;
const char *moves[5] = {"rock", "paper", "scissors", "lizard", "Spock"};
// winner[i][j] is a skew-symmetric matrix which is:
//  -1 if i beats j
//  +1 if j beats i
//   0 if draw (diagonal entries)
const int winner[5][5] = {
	{ 0,  1, -1, -1,  1},
	{-1,  0,  1,  1, -1},
	{ 1, -1,  0, -1,  1},
	{ 1, -1,  1,  0, -1},
	{-1,  1, -1,  1,  0}
};

map<vi, int> cnt;

vector<int> hist;

void make_move(int i) {
	printf("%s\n", moves[i]);
	fflush(stdout);
	char reply[1000];
	scanf("%s", reply);
	for (int j = 0; j < 5; ++j)
		if (!strcmp(moves[j], reply)) {
			hist.push_back(j);
			return;
		}
	assert(0);
}

int main(void) {
	int rounds;
	scanf("%d", &rounds);
	for (int i = 0; i < N; ++i) {
		make_move(2);
	}
	for (int i = N; i < rounds; ++i) {
		++cnt[hist];
		vi cand(5);
		hist.erase(hist.begin());
		hist.push_back(0);
		for (int j = 0; j < 5; ++j) {
			hist.back() = j;
			int c = cnt[hist];
			for (int k = 0; k < 5; ++k)
				if (winner[k][j] == -1) cand[k] += c;
		}
		hist.pop_back();
		int bestc = 0, bestj = 0;
		for (int j = 0; j < 5; ++j)
			if (cand[j] > bestc)
				bestc = cand[j], bestj = j;
		fprintf(stderr, "move %d, bestj = %d, bestc = %d\n",
				i+1, bestj, bestc);
		make_move(bestj);
	}
	return 0;
}
