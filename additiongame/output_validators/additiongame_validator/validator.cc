#include <utility>
#include <set>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include "streamcorr.h"

using namespace std;

int main(int argc, char **argv) {
  init_io(argc, argv);

	int n;
	judge_in >> n;

	vector<int> a(n, 0), pi(n, 0), sigma(n, 0);
	for(int i = 0; i < n; ++i)
		judge_in >> a[i];

	int s = 0;
	for(int i = 0; i < n; ++i) s = (s + a[i]) % n;

	if(s != 0) {
		string str;
		if(!(author_out >> str))
			report_error("");
		if(str != "impossible")
			report_error("Wrong answer");
	} else {
		for(int i = 0; i < n; ++i) {
			if(!(author_out >> pi[i])) {
				report_error("Bad output from submission.");
			}
		}
		for(int i = 0; i < n; ++i) {
			if(!(author_out >> sigma[i])) {
				report_error("Bad output from submission.");
			}
		}

		for(int i = 0; i < n; ++i) {
			if(! (1 <= sigma[i] && sigma[i] <= n && 1 <= pi[i] && pi[i] <= n) )
				report_error("Bad entries in the output sequences.");
		}
		
		set<int> S, P;
		for(int i = 0; i < n; ++i) {
			S.insert(sigma[i]);
			P.insert(pi[i]);
		}
		if(! (S.size() == n && P.size() == n) )
			report_error("The output sequences do not form permutations.");


		for(int i = 0; i < n; ++i) {
			if(a[i] % n != (pi[i] + sigma[i]) % n) {
				report_error("The sum of the permutations is not right.");
			}
		}
	}
  accept();
}
