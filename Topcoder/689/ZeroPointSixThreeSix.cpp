#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class ZeroPointSixThreeSix {
public:
    vector <int> replan(vector <int> x, vector <int> y, vector <int> match);
};

vector <int> ZeroPointSixThreeSix::replan(vector <int> x, vector <int> y, vector <int> match) {

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
			int x[]                   = {0,0,1,1};
			int y[]                   = {0,1,0,1};
			int match[]               = {3,2,1,0};
			int expected__[]          = {1, 0, 3, 2 };

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {0,0,4,4};
			int y[]                   = {0,3,0,3};
			int match[]               = {3,2,1,0};
			int expected__[]          = {2, 3, 0, 1 };

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {0,0,4,4};
			int y[]                   = {0,3,0,3};
			int match[]               = {1,0,3,2};
			int expected__[]          = {2, 3, 0, 1 };

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {-1,1,100,100,1,-1,-100,-100};
			int y[]                   = {100,100,1,-1,-100,-100,-1,1};
			int match[]               = {1,0,3,2,5,4,7,6};
			int expected__[]          = {1, 0, 3, 2, 5, 4, 7, 6 };

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {-1,1,100,100,1,-1,-100,-100};
			int y[]                   = {100,100,1,-1,-100,-100,-1,1};
			int match[]               = {2,3,0,1,6,7,4,5};
			int expected__[]          = {7, 2, 1, 4, 3, 6, 5, 0 };

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int x[]                   = {-9331, -7945, 697, 7897, 3789, -4517, -7995, 6145, -3842, -3234, -4150, -4414, -8065, 7381, -6647, -4401};
			int y[]                   = {2058, -5482, 5501, -3207, -3836, -2061, 9589, 8487, -3062, -3736, 1491, 1424, 7285, -6753, 3937, -1084};
			int match[]               = {3, 2, 1, 0, 11, 10, 8, 15, 6, 12, 5, 4, 9, 14, 13, 7};
			int expected__[]          = {1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14 };

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int match[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int match[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			int x[]                   = ;
			int y[]                   = ;
			int match[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ZeroPointSixThreeSix().replan(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(match, match + (sizeof match / sizeof match[0])));
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
