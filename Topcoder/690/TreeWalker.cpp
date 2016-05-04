#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;
const lint inv2 = 500000004;

vector<int> adj[MAXN];
lint p2[MAXN];
lint rootsum[MAXN];

class TreeWalker {
public:
    int calc(int N, int A0, int B, int C, int MD);
};

lint dfs(int v, int prv, int n) {
    lint ret = p2[n];
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        ret += inv2*dfs(nxt, v, n);
        ret %= MOD;
    }
    return rootsum[v] = ret;
}

lint go(int v, int prv, lint upsum, int n) {
    lint ret = upsum + rootsum[v] - p2[n];
    ret = (ret%MOD + MOD)%MOD;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        lint children = rootsum[v] - (rootsum[nxt]*inv2);
        children = (children%MOD + MOD)%MOD;
        lint newupsum = ((upsum*inv2 + children*inv2)%MOD + MOD)%MOD;        
        ret += go(nxt, v, newupsum, n);
        ret %= MOD;
    }
    return ret;        
}

int TreeWalker::calc(int N, int A0, int B, int C, int MD) {
    for (int v = 0; v < N; v++) adj[v].clear();
    p2[0] = 1;
    for (int p = 1; p < MAXN; p++)
        p2[p] = (p2[p - 1] * 2)%MOD;
    
    vector<lint> A = {A0};
    for (int i = 1; i <= N - 2; i++)
        A.push_back((A[i - 1]*B + C)%MD);
    for (int v = 0; v < N; v++) adj[v].clear();
    for (int i = 1; i <= N - 1; i++) {
        int j = A[i - 1]%i;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    dfs(0, -1, N);
    return inv2*go(0, -1, 0, N)%MOD;
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
			int N                     = 4;
			int A0                    = 0;
			int B                     = 1;
			int C                     = 1;
			int MOD                   = 1000;
			int expected__            = 34;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 10;
			int A0                    = 0;
			int B                     = 0;
			int C                     = 0;
			int MOD                   = 1;
			int expected__            = 13824;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 16;
			int A0                    = 15;
			int B                     = 1;
			int C                     = 1;
			int MOD                   = 16;
			int expected__            = 917506;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 1000;
			int A0                    = 385498676;
			int B                     = 349131547;
			int C                     = 115776323;
			int MOD                   = 614879544;
			int expected__            = 245566366;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 100000;
			int A0                    = 111222333;
			int B                     = 444555666;
			int C                     = 777888999;
			int MOD                   = 123456789;
			int expected__            = 119729770;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int N                     = ;
			int A0                    = ;
			int B                     = ;
			int C                     = ;
			int MOD                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int A0                    = ;
			int B                     = ;
			int C                     = ;
			int MOD                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int A0                    = ;
			int B                     = ;
			int C                     = ;
			int MOD                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TreeWalker().calc(N, A0, B, C, MOD);
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
