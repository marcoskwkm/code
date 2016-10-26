#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class PartisanGame {
public:
    string getWinner(int n, vector <int> a, vector <int> b);
};

const int MAXN = (int)1e6 + 10;
const int MAGIC = 360360;

int dp[2][MAXN];
vector<int> v[2];
int t = 0;
bool go(int p, int n) {
    if (n == 0) return 0;
    if (dp[p][n] != -1) return dp[p][n];
    for (int x: v[p])
        if (n >= x && !go(p ^ 1, n - x))
            return (dp[p][n] = 1);
    return (dp[p][n] = 0);
}        

string PartisanGame::getWinner(int n, vector <int> a, vector <int> b) {
    t++;
    v[0] = a, v[1] = b;
    memset(dp, -1, sizeof(dp));
    while (n >= MAXN) n -= MAGIC;
    return go(0, n) ? "Alice" : "Bob";
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int n                     = 7;
			int a[]                   = {3, 4};
			int b[]                   = {4};
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 10;
			int a[]                   = {1};
			int b[]                   = {4, 3, 2};
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 104982;
			int a[]                   = {2, 3, 4, 5};
			int b[]                   = {2, 5};
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 999999999;
			int a[]                   = {4};
			int b[]                   = {5};
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 1000000000;
			int a[]                   = {1,2,3,4,5};
			int b[]                   = {1,2,3,4,5};
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int n                     = 2541;
			int a[]                   = {2, 3, 4, 5};
			int b[]                   = {5};
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int n                     = ;
			int a[]                   = ;
			int b[]                   = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int a[]                   = ;
			int b[]                   = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PartisanGame().getWinner(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
