#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr, x)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct RearrangeAndIncrement {
    vector<int> change(int X, int Y);
};

vector<int> RearrangeAndIncrement::change(int X, int Y) {
    vector<int> ans = {X};
    string str_y = to_string(Y);

    auto reduce = [&](int n) {
        string s = to_string(n);

        for (char &c: s) {
            if (c == '0') {
                swap(c, s[0]);
                int nx;
                sscanf(s.c_str(), "%d", &nx);
                ans.push_back(nx);
                return nx;
            }
        }

        int add = 10 - n % 10;
        n += add;
        ans.push_back(n);
        n /= 10;
        ans.push_back(n);
        return n;
    };

    auto increase = [&](int n) {
        string s = to_string(n);

        if (all_of(s.begin(), s.end(), [](char c) { return c == '9'; })) {
            n += 1;
            ans.push_back(n);
            return n;
        }

        if (n % 10 == 9) {
            for (size_t i = 0; i < s.size(); i++) {
                if (s[i] != '9') {
                    swap(s[i], s.back());
                    int nx;
                    sscanf(s.c_str(), "%d", &nx);
                    ans.push_back(nx);
                    return nx;
                }
            }
        } else {
            int add = 9 - n % 10;
            n += add;
            ans.push_back(n);
            return n;
        }
    };

    while (X > 1) {
        X = reduce(X);
    }

    if (Y < 10) {
        if (X < Y) {
            ans.push_back(Y);
        }
        return ans;
    }

    while (to_string(X).size() < str_y.size()) {
        X = increase(X);
    }

    if (X == Y) {
        return ans;
    }

    bool add_one = false;

    if (all_of(str_y.begin() + 1, str_y.end(), [](char c) { return c == '0'; })) {
        add_one = true;
        Y -= 1;
        str_y = to_string(Y);
    }

    if (str_y[0] > '1') {
        X += str_y[0] - '0';
        ans.push_back(X);
        string str_x = to_string(X);
        swap(str_x[0], str_x.back());
        sscanf(str_x.c_str(), "%d", &X);
        ans.push_back(X);
    }

    for (size_t i = 1; i < str_y.size(); i++) {
        if (str_y[i] == '0') {
            continue;
        }

        int add = str_y[i] - '0' - (X % 10);

        if (add > 0) {
            X += add;
            ans.push_back(X);
        }

        if (i + 1 < str_y.size()) {
            string str_x = to_string(X);
            swap(str_x[i], str_x.back());
            sscanf(str_x.c_str(), "%d", &X);
            ans.push_back(X);
        }
    }

    if (add_one) {
        ans.push_back(X + 1);
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
        int X = 10234;
        int Y = 1247;
        int expected__[] = {10234, 1234, 1247};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RearrangeAndIncrement().change(X, Y);
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 1: {
        int X = 10234;
        int Y = 10248;
        int expected__[] = {10234, 10244, 10248};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RearrangeAndIncrement().change(X, Y);
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 2: {
        int X = 999997;
        int Y = 1000001;
        int expected__[] = {999997, 999998, 999999, 1000000, 1000001};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RearrangeAndIncrement().change(X, Y);
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 3: {
        int X = 1000000;
        int Y = 1000;
        int expected__[] = {1000000, 1000};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RearrangeAndIncrement().change(X, Y);
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 4: {
        int X = 1111111;
        int Y = 1111232;
        int expected__[] = {1111111, 1111122, 1111221, 1111232};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RearrangeAndIncrement().change(X, Y);
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 5: {
        int X = 47;
        int Y = 47;
        int expected__[] = {47};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RearrangeAndIncrement().change(X, Y);
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }

        // custom cases

    case 6: {
        int X = 1;
        int Y = 10;
        int expected__[] = {};

        std::clock_t start__ = std::clock();
        vector<int> received__ = RearrangeAndIncrement().change(X, Y);
        return verify_case(
            casenum__,
            vector<int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
        /*      case 7: {
                                int X                     = ;
                                int Y                     = ;
                                int expected__[]          = ;

                                std::clock_t start__      = std::clock();
                                vector <int> received__   = RearrangeAndIncrement().change(X, Y);
                                return verify_case(casenum__, vector <int>(expected__, expected__ +
           (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
                        }*/
        /*      case 8: {
                                int X                     = ;
                                int Y                     = ;
                                int expected__[]          = ;

                                std::clock_t start__      = std::clock();
                                vector <int> received__   = RearrangeAndIncrement().change(X, Y);
                                return verify_case(casenum__, vector <int>(expected__, expected__ +
           (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
