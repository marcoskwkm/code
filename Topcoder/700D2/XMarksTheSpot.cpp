#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class XMarksTheSpot {
public:
    int countArea(vector <string> board);
};

const int MAXN = 55;

int XMarksTheSpot::countArea(vector <string> board) {
    int n = board.size(), m = board[0].size();
    vector<pii> unknown;
    int L = INF, R = 0, T = INF, B = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (board[r][c] == 'O') {
                L = min(L, c); R = max(R, c);
                T = min(T, r); B = max(B, r);
            }
            else if (board[r][c] == '?')
                unknown.push_back(pii(r, c));
        }
    }
                
    int k = unknown.size();
    int ans = 0;
    for (int mask = 0; mask < (1 << k); mask++) {
        int l = L, r = R, t = T, b = B;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                l = min(l, unknown[i].second);
                r = max(r, unknown[i].second);
                t = min(t, unknown[i].first);
                b = max(b, unknown[i].first);
            }
        }
        ans += (r - l + 1) * (b - t + 1);
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
			string board[]            = {
"?.",
".O"
};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {
"???",
"?O?",
"???"
};
			int expected__            = 1952;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {
"...?.",
"?....",
".O...",
"..?..",
"....?"
};
			int expected__            = 221;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"OOOOOOOOOOOOOOOOOOOOO"};
			int expected__            = 21;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"?????????OO??????????"};
			int expected__            = 9963008;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {
"OOO",
"O?O",
"OOO",
"..."
};
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XMarksTheSpot().countArea(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
