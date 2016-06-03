#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

class Sunnygraphs {
public:
    long long count(vector <int> a);
};

vector<int> nxt;

long long Sunnygraphs::count(vector <int> a) {
    int n = a.size();
    nxt = a;
    
    set<int> reach0, reach1;
    int v0 = 0, v1 = 1;
    while (reach0.find(v0) == reach0.end()) {
        reach0.insert(v0);
        v0 = nxt[v0];
    }
    while (reach1.find(v1) == reach1.end()) {
        reach1.insert(v1);
        v1 = nxt[v1];
    }

    int common = 0;
    int notin0 = 0, notin1 = 0;
    for (int x: reach0) {
        if (reach1.find(x) != reach1.end())
            common++;
        else
            notin1++;
    }
    for (int x: reach1)
        if (reach0.find(x) == reach0.end())
            notin0++;
    int total = reach0.size() + reach1.size() - common;
    lint ans = 0;
//    printf("%d %d %d\n", notin0, notin1, total);
    if (notin0) ans += ((1ll << notin0) - 1) * (1ll << (n - total));
    if (notin1) ans += ((1ll << notin1) - 1) * (1ll << (n - total));
    if (common == 0) ans += (1ll << (n - total));
    return (1ll << n) - ans;
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
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
			int a[]                   = {1,0};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {2,2,0};
			long long expected__      = 7;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {2,3,0,1};
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {2,2,3,4,3};
			long long expected__      = 30;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {18,18,20,28,7,27,8,13,40,3,7,21,30,17,13,34,29,16,15,11,0,9,39,36,38,23,24,8,4,9,29,22,35,5,13,23,3,27,34,23,8};
			long long expected__      = 2198754820096LL;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
          int a[]                   = {2, 3, 0, 1, 5, 4};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int a[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Sunnygraphs().count(vector <int>(a, a + (sizeof a / sizeof a[0])));
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
