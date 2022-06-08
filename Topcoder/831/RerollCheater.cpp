#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr, x)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct RerollCheater {
    vector<int> reroll(vector<int> currentDice, vector<int> futureRolls);
};

vector<int> RerollCheater::reroll(vector<int> currentDice, vector<int> futureRolls) {
    int n = currentDice.size();

    vector<pii> all;
    for (int i = 0; i < n; i++) {
        all.push_back(pii(currentDice[i], i + 1));
    }
    for (int i = 0; i < (int)futureRolls.size(); i++) {
        all.push_back(pii(futureRolls[i], -(i + 1)));
    }

    sort(all.begin(), all.end(), greater<pii>());

    vector<bool> keep(n, 0);
    vector<int> rolls;

    for (int i = 0; i < n; i++) {
        if (all[i].second > 0) {
            keep[all[i].second - 1] = 1;
        } else {
            rolls.push_back(-all[i].second);
        }
    }

    sort(rolls.begin(), rolls.end(), greater<int>());

    vector<int> ans;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (keep[i]) {
            continue;
        }
        while (cur < rolls.back()) {
            cur++;
            ans.push_back(i);
        }
        rolls.pop_back();
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

template<typename T> std::ostream &operator<<(std::ostream &os, const vector<T> &v) {
    os << "{";
    for (typename vector<T>::const_iterator vi = v.begin(); vi != v.end(); ++vi) {
        if (vi != v.begin())
            os << ",";
        os << " " << *vi;
    }
    os << " }";
    return os;
}

int verify_case(int casenum, const vector<int> &expected, const vector<int> &received,
                std::clock_t elapsed) {
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
        int currentDice[] = {1, 2, 1, 1, 1, 1};
        int futureRolls[] = {20, 20, 20};
        int expected__[] = {3, 4, 5};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RerollCheater().reroll(
            vector<int>(currentDice, currentDice + (sizeof currentDice / sizeof currentDice[0])),
            vector<int>(futureRolls, futureRolls + (sizeof futureRolls / sizeof futureRolls[0])));
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 1: {
        int currentDice[] = {4, 7, 13, 19};
        int futureRolls[] = {1, 1, 2, 3, 1, 4, 1, 3};
        int expected__[] = {};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RerollCheater().reroll(
            vector<int>(currentDice, currentDice + (sizeof currentDice / sizeof currentDice[0])),
            vector<int>(futureRolls, futureRolls + (sizeof futureRolls / sizeof futureRolls[0])));
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 2: {
        int currentDice[] = {18, 11, 15, 12};
        int futureRolls[] = {3, 14, 9};
        int expected__[] = {1, 1};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RerollCheater().reroll(
            vector<int>(currentDice, currentDice + (sizeof currentDice / sizeof currentDice[0])),
            vector<int>(futureRolls, futureRolls + (sizeof futureRolls / sizeof futureRolls[0])));
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }

        // custom cases

        /*      case 3: {
                                int currentDice[]         = ;
                                int futureRolls[]         = ;
                                int expected__[]          = ;

                                std::clock_t start__      = std::clock();
                                vector <int> received__   = RerollCheater().reroll(vector
           <int>(currentDice, currentDice + (sizeof currentDice / sizeof currentDice[0])), vector
           <int>(futureRolls, futureRolls + (sizeof futureRolls / sizeof futureRolls[0]))); return
           verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof
           expected__[0])), received__, clock()-start__);
                        }*/
        /*      case 4: {
                                int currentDice[]         = ;
                                int futureRolls[]         = ;
                                int expected__[]          = ;

                                std::clock_t start__      = std::clock();
                                vector <int> received__   = RerollCheater().reroll(vector
           <int>(currentDice, currentDice + (sizeof currentDice / sizeof currentDice[0])), vector
           <int>(futureRolls, futureRolls + (sizeof futureRolls / sizeof futureRolls[0]))); return
           verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof
           expected__[0])), received__, clock()-start__);
                        }*/
        /*      case 5: {
                                int currentDice[]         = ;
                                int futureRolls[]         = ;
                                int expected__[]          = ;

                                std::clock_t start__      = std::clock();
                                vector <int> received__   = RerollCheater().reroll(vector
           <int>(currentDice, currentDice + (sizeof currentDice / sizeof currentDice[0])), vector
           <int>(futureRolls, futureRolls + (sizeof futureRolls / sizeof futureRolls[0]))); return
           verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof
           expected__[0])), received__, clock()-start__);
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
