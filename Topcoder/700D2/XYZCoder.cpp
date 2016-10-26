#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class XYZCoder {
public:
    int countWays(int room, int size);
};

const int MAXN = 110;
const int MOD = (int)1e9 + 7;
lint dp[MAXN][MAXN*MAXN];
lint acc[MAXN][MAXN*MAXN];
int n, m;

int XYZCoder::countWays(int room, int size) {
    for (int j = room - 1; j <= room*size; j++) {
        dp[room - 1][j] = 1;
        acc[room - 1][j] = 1 + (j > 0 ? acc[room - 1][j - 1] : 0);
    }
    for (int i = room - 2; i >= 0; i--) {
        for (int j = i; j <= room*size; j++) {
            int rem = (i + 1)*size - j;
            dp[i][j] = (acc[i + 1][j + rem] - acc[i + 1][j]) % MOD;
            acc[i][j] = dp[i][j] + (j > 0 ? acc[i][j - 1] : 0);
            acc[i][j] %= MOD;
        }
    }
            
    lint ret = dp[0][0];
    for (int f = 2; f <= room; f++)
        ret = (ret * f) % MOD;
    return (ret % MOD + MOD) % MOD;
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
			int room                  = 2;
			int size                  = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int room                  = 1;
			int size                  = 2;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int room                  = 2;
			int size                  = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int room                  = 4;
			int size                  = 5;
			int expected__            = 6840;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int room                  = 100;
			int size                  = 100;
			int expected__            = 718243627;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int room                  = ;
			int size                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int room                  = ;
			int size                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int room                  = ;
			int size                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XYZCoder().countWays(room, size);
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
