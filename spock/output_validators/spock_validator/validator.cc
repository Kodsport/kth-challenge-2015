#include <utility>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include "streamcorr.h"

const bool DEBUG = true;

#define dprintf DEBUG && fprintf

using namespace std;
typedef pair<int, int> pii;

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

int modinv[2*p];

void init() {
	for (int x = 1; x < p; ++x)
		for(int y = 1; y < p; ++y)
			if (x*y % p == 1)
				modinv[x] = modinv[x+p] = y;
}

void print_move(int move) {
	printf("%s\n", moves[move]);
	fflush(stdout);
}

int read_move(int round) {
	char str[1000];
	if (scanf("%900s", str) != 1) {
		report_error("Round %d: couldn't read a string\n", round);
	}
	for (int i = 0; i < 5; ++i)
		if (!strcasecmp(str, moves[i])) return i;
	report_error("Round %d: got an invalid move '%s'\n", round, str);
	return -1;
}

struct state {
	int x, a, b;
	state(int x=0, int a=0, int b=0): x(x), a(a), b(b) {}
	void advance() { x = (a*x+b)%p; }
};

void all_possibilities(int m1, int m2, int m3, vector<state> &R) {
	for (int x1 = m1; x1 < p; x1 += 5)
		for (int x2 = m2; x2 < p; x2 += 5) {
			if (x1 != x2) {
				for (int x3 = m3; x3 < p; x3 += 5) {
					int a = (p+x3-x2)*modinv[p+x2-x1] % p;
					int b = (p*p+x3-a*x2)%p;
					R.push_back(state(x3, a, b));
				}
			} else if (m3 == m1) {
				for (int a = 0; a < p; ++a) {
					int b = (p*p + x2 - a*x1) % p;
					R.push_back(state(x1, a, b));
				}
			}
		}
	
}

int play(int rounds) {
	string mode;
	vector<state> cands;
	vector<int> compmoves;
	vector<int> submoves;
	assert(judge_in >> mode);

	report_feedback(judgemessage, "Playing %d rounds following '%s' strategy\n",
					rounds, mode.c_str());

	int r = 1;
	assert(mode == "fixed" ||
		   mode == "adaptive_random" ||
		   mode == "adaptive_deterministic" ||
		   mode == "adaptive_cautious");
	if (mode == "fixed") {
		int x, a, b;
		assert(judge_in >> x >> a >> b);
		cands.push_back(state(x, a, b));
	} else {
		// for random mode, get seed to use
		if (mode == "adaptive_random") {
			int seed;
			assert(judge_in >> seed);
			report_feedback(judgemessage, "Random seed is %d\n", seed);
			srandom(seed);
		}

		// one of the adaptive modes
		// first play 3 rounds where we just play annoyingly, in order
		// to reduce number of states to consider (as in solution)
		for (; r <= 3; ++r) {
			submoves.push_back(read_move(r));
			vector<int> poss;
			for (int i = 0; i < 5; ++i)
				if (winner[i][submoves.back()] == -1)
					poss.push_back(i);
			compmoves.push_back(poss[random() % 2]);
			print_move(compmoves.back());
		}
		all_possibilities(compmoves[0], compmoves[1], compmoves[2], cands);

		report_feedback(judgemessage, "After initial three rounds, have %d cands\n",
						cands.size());
	}

	for (; r <= rounds; ++r) {
		submoves.push_back(read_move(r));

		vector<pii> poss(5);
		bool canwin = false;
		for (int i = 0; i < 5; ++i) poss[i].second = i;
		for (auto &st: cands) {
			st.advance();
			++poss[st.x % 5].first;
			canwin |= (winner[submoves.back()][st.x % 5] != -1);
		}

		dprintf(stderr, "[DEBUG validator]: move %d, got %d, I have %d cands, canwin %d\n",
				r, submoves.back(), cands.size(), canwin);

		if (canwin && mode != "adaptive_cautious")
			for (int i = 4; i >= 0; --i)
				if (winner[submoves.back()][i] == -1)
					poss.erase(poss.begin()+i);
		
		if (mode == "fixed" || mode == "adaptive_deterministic") {
			compmoves.push_back(max_element(poss.begin(), poss.end())->second);
		} else if (mode == "adaptive_random") {
			int tot = 0;
			for (auto p: poss) tot += p.first;
			int choice = random() % tot;
			for (auto p: poss) {
				choice -= p.first;
				if (choice < 0) {
					compmoves.push_back(p.second);
					dprintf(stderr, "[DEBUG validator]: chose %d (prob %d/%d)\n",
							p.second, p.first, tot);
					break;
				}
			}
			assert(choice < 0);
		} else if (mode == "adaptive_cautious") {
			pii maxa = *max_element(poss.begin(), poss.end());
			pii maxv = pii(0, -1);
			for (auto p: poss)
				if (winner[submoves.back()][p.second] != -1)
					maxv = max(maxv, p);
			int move = 2*maxv.first > maxa.first ? maxv.second : maxa.second;
			compmoves.push_back(move);
			dprintf(stderr, "[DEBUG validator]: maxa = %d (%d), maxv = %d (%d), choose %d\n",
					maxa.first, maxa.second, maxv.first, maxv.second, move);
			
		}

		vector<state> newcands;
		for (auto &C: cands)
			if (C.x % 5 == compmoves.back())
				newcands.push_back(C);
		swap(cands, newcands);

		print_move(compmoves.back());
	}

	int submission_wins = 0;
	for (int i = 0; i < rounds; ++i)
		submission_wins += (winner[submoves[i]][compmoves[i]] == -1);
	return submission_wins;
}

int main(int argc, char **argv) {
  init_io(argc, argv);
  init();

  int rounds;
  assert(judge_in >> rounds);
  printf("%d\n", rounds);
  fflush(stdout);
  
  int submission_wins = play(rounds);
  report_feedback(judgemessage, "Submission won %d/%d ~ %.2f%% of the rounds\n",
				   submission_wins, rounds, 100.0*submission_wins/rounds);
  if (5*submission_wins < 4*rounds) {
	  report_error("Not enough wins.");
  }
  /* Yay! */
  accept();
}
