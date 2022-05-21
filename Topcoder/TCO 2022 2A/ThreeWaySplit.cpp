#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct ThreeWaySplit {
    string split(vector <int> loot);
};

string ThreeWaySplit::split(vector <int> loot) {

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
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
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
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int loot[]                = {4, 7, 53};
			string expected__         = "CCC";

			std::clock_t start__      = std::clock();
			string received__         = ThreeWaySplit().split(vector <int>(loot, loot + (sizeof loot / sizeof loot[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int loot[]                = {1, 1, 1, 4, 1};
			string expected__         = "BBBAB";

			std::clock_t start__      = std::clock();
			string received__         = ThreeWaySplit().split(vector <int>(loot, loot + (sizeof loot / sizeof loot[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int loot[]                = {47, 47, 47};
			string expected__         = "CBA";

			std::clock_t start__      = std::clock();
			string received__         = ThreeWaySplit().split(vector <int>(loot, loot + (sizeof loot / sizeof loot[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int loot[]                = {1, 2, 3, 4, 5, 6};
			string expected__         = "CBBABA";

			std::clock_t start__      = std::clock();
			string received__         = ThreeWaySplit().split(vector <int>(loot, loot + (sizeof loot / sizeof loot[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int loot[]                = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = ThreeWaySplit().split(vector <int>(loot, loot + (sizeof loot / sizeof loot[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int loot[]                = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = ThreeWaySplit().split(vector <int>(loot, loot + (sizeof loot / sizeof loot[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int loot[]                = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = ThreeWaySplit().split(vector <int>(loot, loot + (sizeof loot / sizeof loot[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}
 

#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
