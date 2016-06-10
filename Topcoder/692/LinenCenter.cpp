#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class LinenCenter {
public:
    int countStrings(string S, int N, int K);
};

int LinenCenter::countStrings(string S, int N, int K) {

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
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
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
			string S                  = "xy";
			int N                     = 2;
			int K                     = 1;
			int expected__            = 2079;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S                  = "q";
			int N                     = 2;
			int K                     = 1;
			int expected__            = 1926;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S                  = "ababab";
			int N                     = 5;
			int K                     = 4;
			int expected__            = 527166180;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S                  = "fgcdx";
			int N                     = 500;
			int K                     = 10;
			int expected__            = 942389748;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S                  = "ghjhhhgjhjhgjhghghjhjg";
			int N                     = 8;
			int K                     = 10000000;
			int expected__            = 618639712;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S                  = "pdpfrpfdfdpfdpfdpfpdfldfpfldpfdlfpdlfdpflepflfldpflofpwpldlfpde";
			int N                     = 999;
			int K                     = 500000000;
			int expected__            = 852730493;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string S                  = "a";
			int N                     = 100;
			int K                     = 0;
			int expected__            = 990669582;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			string S                  = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
			int N                     = 1000;
			int K                     = 1000000000;
			int expected__            = 286425258;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			string S                  = ;
			int N                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string S                  = ;
			int N                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			string S                  = ;
			int N                     = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = LinenCenter().countStrings(S, N, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
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
