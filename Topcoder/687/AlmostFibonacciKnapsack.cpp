#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class AlmostFibonacciKnapsack {
public:
    vector <int> getIndices(long long x);
};

vector <int> AlmostFibonacciKnapsack::getIndices(long long x) {
    vector<lint> fib = {2, 3};
    while (fib.back() < (lint)1e18)
        fib.push_back(fib[fib.size() - 2] + fib[fib.size() - 1] - 1);
    vector<int> ans;
    for (int i = fib.size() - 1; i >= 0; i--) {
        if (x >= fib[i] && x - fib[i] != 1) {
            ans.push_back(i + 1);
            x -= fib[i];
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
			long long x               = 148;
			int expected__[]          = {6, 10, 8, 5 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			long long x               = 2;
			int expected__[]          = {1 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			long long x               = 13;
			int expected__[]          = {2, 3, 4 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			long long x               = 3;
			int expected__[]          = {2 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			long long x               = 86267769395LL;
			int expected__[]          = {3, 14, 15, 9, 26, 53, 5, 8 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long x               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			long long x               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			long long x               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices(x);
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
