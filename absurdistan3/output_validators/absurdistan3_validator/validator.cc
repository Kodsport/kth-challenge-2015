#include <utility>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include "streamcorr.h"

#include <sstream>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;

bool author_messages = false;

/* Wrapper for author message printing so that they are only printed in
 * case the author_messages option was given.  If the validator should
 * always print author messages, you can just call
 * report_feedback(authormessage, ...) directly.
 */
void author_message(const char *s) {
    if (author_messages) {
        report_feedback(authormessage, s);
    }
}

/* Check one test case. */
void check_case() {
    int n;
    judge_in >> n;
    vector<pii> a(n), b(n);
    for(int i = 0; i < n; ++i) {
        judge_in >> a[i].first >> a[i].second;
        if (a[i].first > a[i].second)
            swap(a[i].first, a[i].second);
    }
    sort(a.begin(), a.end());

    vector<bool> seen(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!(author_out >> b[i].first >> b[i].second))
            report_error("Wrong output format");
        if (b[i].first < 1 || b[i].first > n)
            report_error("Output out of range");

        int q = b[i].first - 1;
        if (seen[q])
            report_error("Too many roads associated with city %d", q);
        seen[q] = true;

        if (b[i].first > b[i].second)
            swap(b[i].first, b[i].second);
    }
    sort(b.begin(), b.end());

    if (a != b)
        report_error("Wrong roads in the output");
}

int main(int argc, char **argv) {
    init_io(argc, argv);
    /* Check if the author_messages option is given. */
    for (int i = 4; i < argc; ++i)
        if (!strcmp(argv[i], "author_messages"))
            author_messages = true;

    check_case();

    /* Check for trailing output in author file. */
    string trash;
    if (author_out >> trash) {
        author_message("Trailing output after last test case");
        report_error("Trailing output");
    }

    /* Yay! */
    author_message("Thank you for your great code. It was fantastic.");
    accept();
}
