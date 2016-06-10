#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class Moneymanager {
public:
    int getbest(vector <int> a, vector <int> b, int X);
};

const int MAXN = 30;
const int MAXS = 260;

int dp[MAXN][MAXN][MAXS];
int sb[2*MAXN];

int Moneymanager::getbest(vector <int> a, vector <int> b, int X) {
    int n = a.size();
    vector<pii> v;
    for (int i = 0; i < n; i++)
        v.push_back(pii(a[i], b[i]));
    sort(v.begin(), v.end(), [](pii a, pii b) {
        return a.first * b.second < b.first * a.second;
    });

    sb[0] = v[0].second;
    for (int i = 1; i < n; i++)
        sb[i] = sb[i - 1] + v[i].second;

    int ans = 0;
    for (int sb2 = 0; sb2 < MAXS; sb2++) {
        int sb1 = sb[n - 1] - sb2;
        for (int i = 0; 2 * i <= n; i++)
            for (int j = 0; 2 * j <= n; j++)
                for (int s = 0; s < MAXS; s++)
                    dp[i][j][s] = -INF;
        dp[0][0][0] = 0;
        for (int q = 0; q < n; q++) {
            for (int i = 0; 2*i <= n && i <= q; i++) {
                int j = q - i;
                int cur = i + j;
                for (int s = 0; s < MAXS; s++) {
                    int s2 = q ? sb[q - 1] - s : 0;
                    if (dp[i][j][s] == -INF) continue;
                    if (2*i < n) dp[i + 1][j][s + v[cur].second] = max(dp[i + 1][j][s + v[cur].second], dp[i][j][s] + (v[cur].second + s + sb2) * v[cur].first);
                    if (2*j < n) dp[i][j + 1][s] = max(dp[i][j + 1][s], dp[i][j][s] + (v[cur].second + s2) * v[cur].first);
                }
            }
        }
        ans = max(ans, dp[n / 2][n / 2][sb1] + sb2 * X);
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
			int a[]                   = {1,1};
			int b[]                   = {2,1};
			int X                     = 0;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = Moneymanager().getbest(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {1,1};
			int b[]                   = {1,5};
			int X                     = 10;
			int expected__            = 61;

			clock_t start__           = clock();
			int received__            = Moneymanager().getbest(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {4,4,6,6};
			int b[]                   = {2,2,3,3};
			int X                     = 100;
			int expected__            = 726;

			clock_t start__           = clock();
			int received__            = Moneymanager().getbest(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {30,13,28,59,26,62,48,75,6,69,94,51};
			int b[]                   = {4,6,4,5,4,3,1,5,6,5,2,2};
			int X                     = 62;
			int expected__            = 22096;

			clock_t start__           = clock();
			int received__            = Moneymanager().getbest(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int a[]                   = ;
			int b[]                   = ;
			int X                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Moneymanager().getbest(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int a[]                   = ;
			int b[]                   = ;
			int X                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Moneymanager().getbest(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			int b[]                   = ;
			int X                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Moneymanager().getbest(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), X);
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
