#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;
const int MOD = (int)1e9 + 7;

class ModEquation {
public:
    vector <int> count(int n, int K, vector <int> query);
};

lint phi;
lint cnt1[MAXN], cnti[MAXN];

lint gcd(lint a, lint b) { return b ? gcd(b, a % b) : a; }

vector <int> ModEquation::count(int n, int K, vector <int> query) {
    phi = K;
    lint k = K;
    for (lint p = 2; p * p <= k; p++) {
        if (k % p == 0) {
            phi = (phi / p) * (p - 1);
            do {k /= p;} while (k % p == 0);
        }
    }
    if (k > 1) phi = (phi / k) * (k - 1);
    debug("phi = %lld\n", phi);
    cnti[0] = 1;
    cnti[1] = phi;
    for (int i = 2; i <= n; i++)
        cnti[i] = (cnti[i - 1] * phi) % MOD;

    vector<int> ans;
    for (int v: query) {
        if (v == 0) {
            lint cnt = 1, cnt2 = 1;
            for (int i = 0; i < n; i++) {
                cnt = (cnt * (K - 1)) % MOD;
                cnt2 = (cnt2 * K) % MOD;
            }
            ans.push_back(((cnt2 - cnt) % MOD + MOD) % MOD);
        }
        else {
            lint d = gcd(v, K);
            if (d == 1) ans.push_back(cnti[n - 1]);
            else {
                lint cnt = 1;
                for (int i = 2; i <= n; i++)
                    cnt = (cnti[i - 1] + cnt) % MOD;
                ans.push_back(cnt);
            }
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
			int n                     = 2;
			int K                     = 2;
			int query[]               = {0,1};
			int expected__[]          = {3, 1 };

			clock_t start__           = clock();
			vector <int> received__   = ModEquation().count(n, K, vector <int>(query, query + (sizeof query / sizeof query[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			int K                     = 4;
			int query[]               = {0,1,2,3};
			int expected__[]          = {8, 2, 4, 2 };

			clock_t start__           = clock();
			vector <int> received__   = ModEquation().count(n, K, vector <int>(query, query + (sizeof query / sizeof query[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int n                     = 6;
			int K                     = 6;
			int query[]               = {4};
			int expected__[]          = {2016 };

			clock_t start__           = clock();
			vector <int> received__   = ModEquation().count(n, K, vector <int>(query, query + (sizeof query / sizeof query[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int n                     = 1;
			int K                     = 2;
			int query[]               = {0,0,0,1,1,1};
			int expected__[]          = {1, 1, 1, 1, 1, 1 };

			clock_t start__           = clock();
			vector <int> received__   = ModEquation().count(n, K, vector <int>(query, query + (sizeof query / sizeof query[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int n                     = ;
			int K                     = ;
			int query[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ModEquation().count(n, K, vector <int>(query, query + (sizeof query / sizeof query[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int n                     = ;
			int K                     = ;
			int query[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ModEquation().count(n, K, vector <int>(query, query + (sizeof query / sizeof query[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int K                     = ;
			int query[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ModEquation().count(n, K, vector <int>(query, query + (sizeof query / sizeof query[0])));
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
