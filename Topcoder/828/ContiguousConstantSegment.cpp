#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
using namespace std;

#define debug(x...) fprintf(stderr, x)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct ContiguousConstantSegment {
    int produce(int N, int MOD, vector<int> Aprefix, int seed, int E);
};

unordered_map<int, int> freq;
set<pii, greater<pii>> pq;

void push(int n) {
    int f = freq[n]++;
    pq.erase(pll(f, n));
    pq.insert(pll(f + 1, n));
}

void pop(int n) {
    int f = freq[n]--;
    pq.erase(pll(f, n));
    pq.insert(pll(f - 1, n));
}

int ContiguousConstantSegment::produce(int N, int MOD, vector<int> Aprefix, int seed, int E) {
    if (N == 1) {
        return 1;
    }

    freq.clear();
    pq.clear();

    int L = Aprefix.size();
    lint state = seed;
    vector<int> seq = Aprefix;
    seq.resize(N);
    for (int i = L; i < N; i++) {
        state = (state * 1103515245 + 12345) % (1LL << 31);
        seq[i] = (state / 16) % MOD;
    }

    int ans = 0;
    int r = -1;
    for (int l = 0; l < N; l++) {
        while (r + 1 < N) {
            push(seq[r + 1]);
            int len = r + 1 - l + 1;
            int diff = len - pq.begin()->first;
            if (diff > E) {
                pop(seq[r + 1]);
                break;
            }
            if (diff == 0) {
                if (E != 1) {
                    ans = max(ans, len);
                } else {
                    ans = max(ans, len - 1);
                }
            } else {
                ans = max(ans, len);
            }
            r++;
        }
        pop(seq[l]);
        int len = r - (l + 1) + 1;
        int diff = len - pq.begin()->first;
        if (diff == 0) {
            if (E != 1) {
                ans = max(ans, len);
            } else {
                ans = max(ans, len - 1);
            }
        } else {
            ans = max(ans, len);
        }
    }

    return ans;
}

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
using std::string;
using std::vector;
int run_test_case(int);
void run_test(int casenum = -1, bool quiet = false) {
    if (casenum != -1) {
        if (run_test_case(casenum) == -1 && !quiet) {
            std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
        }
        return;
    }

    int correct = 0, total = 0;
    for (int i = 0;; ++i) {
        int x = run_test_case(i);
        if (x == -1) {
            if (i >= 100)
                break;
            continue;
        }
        correct += x;
        ++total;
    }

    if (total == 0) {
        std::cerr << "No test cases run." << std::endl;
    } else if (correct < total) {
        std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")."
                  << std::endl;
    } else {
        std::cerr << "All " << total << " tests passed!" << std::endl;
    }
}

int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) {
    std::cerr << "Example " << casenum << "... ";

    string verdict;
    vector<string> info;
    char buf[100];

    if (elapsed > CLOCKS_PER_SEC / 200) {
        std::sprintf(buf, "time %.2fs", elapsed * (1.0 / CLOCKS_PER_SEC));
        info.push_back(buf);
    }

    if (expected == received) {
        verdict = "PASSED";
    } else {
        verdict = "FAILED";
    }

    std::cerr << verdict;
    if (!info.empty()) {
        std::cerr << " (";
        for (size_t i = 0; i < info.size(); ++i) {
            if (i > 0)
                std::cerr << ", ";
            std::cerr << info[i];
        }
        std::cerr << ")";
    }
    std::cerr << std::endl;

    if (verdict == "FAILED") {
        std::cerr << "    Expected: " << expected << std::endl;
        std::cerr << "    Received: " << received << std::endl;
    }

    return verdict == "PASSED";
}

int run_test_case(int casenum__) {
    switch (casenum__) {
    case 0: {
        int N = 9;
        int MOD = 10;
        int Aprefix[] = {1, 2, 3, 2, 4, 5, 2, 2, 6};
        int seed = 47;
        int E = 0;
        int expected__ = 2;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 1: {
        int N = 9;
        int MOD = 10;
        int Aprefix[] = {1, 2, 3, 2, 4, 5, 2, 2, 6};
        int seed = 34424;
        int E = 1;
        int expected__ = 3;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 2: {
        int N = 9;
        int MOD = 10;
        int Aprefix[] = {1, 2, 3, 2, 4, 5, 2, 2, 6};
        int seed = 366122;
        int E = 2;
        int expected__ = 5;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 3: {
        int N = 4700;
        int MOD = 1;
        int Aprefix[] = {0};
        int seed = 123;
        int E = 16;
        int expected__ = 4700;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 4: {
        int N = 20;
        int MOD = 100;
        int Aprefix[] = {0, 42, 47};
        int seed = 123;
        int E = 6;
        int expected__ = 8;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }

        // custom cases

    case 5: {
        int N = 7;
        int MOD = 100;
        int Aprefix[] = {1, 1, 1, 1, 1, 1, 1};
        int seed = 123;
        int E = 3;
        int expected__ = 7;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 6: {
        int N = 7;
        int MOD = 100;
        int Aprefix[] = {2, 2, 1, 2, 1, 1, 1};
        int seed = 123;
        int E = 2;
        int expected__ = 6;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 7: {
        int N = 1;
        int MOD = 100;
        int Aprefix[] = {1};
        int seed = 1;
        int E = 1;
        int expected__ = 1;

        std::clock_t start__ = std::clock();
        int received__ = ContiguousConstantSegment().produce(
            N, MOD, vector<int>(Aprefix, Aprefix + (sizeof Aprefix / sizeof Aprefix[0])), seed, E);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    default:
        return -1;
    }
}
} // namespace moj_harness

#include <cstdlib>
int main(int argc, char *argv[]) {
    if (argc == 1) {
        moj_harness::run_test();
    } else {
        for (int i = 1; i < argc; ++i)
            moj_harness::run_test(std::atoi(argv[i]));
    }
}
// END CUT HERE
