#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

class MultiplicationTable3 {
public:
    vector <int> construct(int x);
};

int cur;
int p[MAXN];

void go(int v, int x) {
    if (x == 2) return;
    assert(x > 2 && x % 2 == 1);
    x -= 1;
    vector<int> divs;
    for (int d = 2; d <= x; d++) {
        while (x % d == 0) {
            divs.push_back(d);
            x /= d;
        }
    }
    for (int d: divs) {
        p[cur] = v;
        go(cur++, d);
    }
}

vector <int> MultiplicationTable3::construct(int x) {
    x++;
    cur = 0;
    while (x % 2 == 0) {
        x /= 2;
        p[cur] = cur;
        cur++;
    }
    if (x > 2) {
        p[cur] = cur;
        cur++;
        go(cur - 1, x);
    }
    vector<int> ans;
    for (int i = 0; i < cur; i++) {
        for (int j = 0; j < cur; j++) {
            if (i == j) ans.push_back(p[i]);
            else ans.push_back(i);
        }
    }
    return ans;            
}

// BEGIN CUT HERE
namespace moj_harness {
    int run_test_case(int);
    void run_test(int casenum = -1, bool quiet = false) {
        if (casenum != -1) {
            if (run_test_case(casenum) == -1 && !quiet) {
                cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
            }
            return;
        }
		
        int correct = 0, total = 0;
        for (int i=0;; ++i) {
            int x = run_test_case(i);
            if (x == -1) {
                if (i >= 100) break;
                continue;
            }
            correct += x;
            ++total;
        }
		
        if (total == 0) {
            cerr << "No test cases run." << endl;
        } else if (correct < total) {
            cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
        } else {
            cerr << "All " << total << " tests passed!" << endl;
        }
    }
	
    template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

    int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) { 
        cerr << "Example " << casenum << "... "; 
		
        string verdict;
        vector<string> info;
        char buf[100];
		
        if (elapsed > CLOCKS_PER_SEC / 200) {
            sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
            info.push_back(buf);
        }
		
        if (expected == received) {
            verdict = "PASSED";
        } else {
            verdict = "FAILED";
        }
		
        cerr << verdict;
        if (!info.empty()) {
            cerr << " (";
            for (int i=0; i<(int)info.size(); ++i) {
                if (i > 0) cerr << ", ";
                cerr << info[i];
            }
            cerr << ")";
        }
        cerr << endl;
		
        if (verdict == "FAILED") {
            cerr << "    Expected: " << expected << endl; 
            cerr << "    Received: " << received << endl; 
        }
		
        return verdict == "PASSED";
    }

    int run_test_case(int casenum__) {
        switch (casenum__) {
        case 0: {
            int x                     = 2;
            int expected__[]          = {1, 1, 1, 1 };

            clock_t start__           = clock();
            vector <int> received__   = MultiplicationTable3().construct(x);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 1: {
            int x                     = 3;
            int expected__[]          = {0, 1, 0, 1 };

            clock_t start__           = clock();
            vector <int> received__   = MultiplicationTable3().construct(x);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 2: {
            int x                     = 6;
            int expected__[]          = {0, 1, 1, 0, 1, 2, 0, 1, 2 };

            clock_t start__           = clock();
            vector <int> received__   = MultiplicationTable3().construct(x);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 3: {
            int x                     = 31;
            int expected__[]          = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };

            clock_t start__           = clock();
            vector <int> received__   = MultiplicationTable3().construct(x);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 4: {
            int x                     = 1;
            int expected__[]          = {0 };

            clock_t start__           = clock();
            vector <int> received__   = MultiplicationTable3().construct(x);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }

            // custom cases

/*      case 5: {
        int x                     = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = MultiplicationTable3().construct(x);
        return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 6: {
        int x                     = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = MultiplicationTable3().construct(x);
        return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 7: {
        int x                     = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = MultiplicationTable3().construct(x);
        return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
        default:
            return -1;
        }
    }
}
 

int main(int argc, char *argv[]) {
    if (argc == 1) {
        moj_harness::run_test();
    } else {
        for (int i=1; i<argc; ++i)
            moj_harness::run_test(atoi(argv[i]));
    }
}
// END CUT HERE
