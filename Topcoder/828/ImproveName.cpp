#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr, x)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;
const int MAXL = 2010;

struct ImproveName {
    int improve(string companyName, int K);
};

lint dp[2][MAXL][30][2];

int ImproveName::improve(string companyName, int K) {
    string s = companyName;
    int n = companyName.size();

    memset(dp, 0, sizeof(dp));

    int cur = 0, prv = 1;
    for (int i = 0; i < 30; i++) {
        dp[prv][0][i][1] = 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        memset(dp[cur], 0, sizeof(cur));
        for (int k = 0; k <= K; k++) {
            for (int last = 0; last < 30; last++) {
                for (int c = 0; c < 2; c++) {
                    lint ret = dp[prv][k][last][c];

                    if (k > 0) {
                        int prv_last = s[i] - 'A' + 1;
                        int prv_c = (c || prv_last < last) ? 1 : 0;
                        ret = (ret + dp[prv][k - 1][prv_last][prv_c]) % MOD;
                    }

                    dp[cur][k][last][c] = ret;
                }
            }
        }
        cur ^= 1;
        prv ^= 1;
    }

    return dp[prv][K][0][0];
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
        string companyName = "ABCDE";
        int K = 2;
        int expected__ = 0;

        std::clock_t start__ = std::clock();
        int received__ = ImproveName().improve(companyName, K);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 1: {
        string companyName = "AABCCDEEEFZ";
        int K = 3;
        int expected__ = 0;

        std::clock_t start__ = std::clock();
        int received__ = ImproveName().improve(companyName, K);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 2: {
        string companyName = "EEDDCCBBAA";
        int K = 3;
        int expected__ = 120;

        std::clock_t start__ = std::clock();
        int received__ = ImproveName().improve(companyName, K);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 3: {
        string companyName = "TOPCODER";
        int K = 8;
        int expected__ = 1;

        std::clock_t start__ = std::clock();
        int received__ = ImproveName().improve(companyName, K);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }
    case 4: {
        string companyName = "TOPCODER";
        int K = 3;
        int expected__ = 49;

        std::clock_t start__ = std::clock();
        int received__ = ImproveName().improve(companyName, K);
        return verify_case(casenum__, expected__, received__, clock() - start__);
    }

        // custom cases

        /*      case 5: {
                                string companyName        = ;
                                int K                     = ;
                                int expected__            = ;

                                std::clock_t start__      = std::clock();
                                int received__            = ImproveName().improve(companyName, K);
                                return verify_case(casenum__, expected__, received__,
           clock()-start__);
                        }*/
        /*      case 6: {
                                string companyName        = ;
                                int K                     = ;
                                int expected__            = ;

                                std::clock_t start__      = std::clock();
                                int received__            = ImproveName().improve(companyName, K);
                                return verify_case(casenum__, expected__, received__,
           clock()-start__);
                        }*/
        /*      case 7: {
                                string companyName        = ;
                                int K                     = ;
                                int expected__            = ;

                                std::clock_t start__      = std::clock();
                                int received__            = ImproveName().improve(companyName, K);
                                return verify_case(casenum__, expected__, received__,
           clock()-start__);
                        }*/
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
