#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class ParenthesesDiv1Medium {
public:
    int minSwaps(string s, vector <int> L, vector <int> R);
};

const int MAXN = 2010;

int nxt[MAXN], prv[MAXN];
bool covered[MAXN];

int ParenthesesDiv1Medium::minSwaps(string s, vector <int> L, vector <int> R) {
    vector<pii> inter;
    set<pii> indep;
    int n = L.size();
    for (int i = 0; i < n; i++) {
        set<int> cuts;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (L[i] < L[j] && R[j] < R[i]) continue;
            if (L[i] < L[j] && L[j] <= R[i]) cuts.insert(L[j] - 1);
            if (L[i] <= R[j] && R[j] < R[i]) cuts.insert(R[j]);
        }
        cuts.insert(R[i]);
        int cur = L[i];
        for (int cut: cuts) {
            indep.insert(pii(cur, cut));
            cur = cut + 1;
        }
    }

    for (int i = 0; i < s.size(); i++) {
        nxt[i] = i + 1;
        prv[i] = i - 1;
    }
    for (int i = 0; i < n; i++) {
        bool in = 0;
        for (pii p: indep) {
            if (p.first < L[i] && R[i] < p.second) {
                in = 1;
                break;
            }
        }
        if (in) indep.insert(pii(L[i], R[i]));
    }
    for (auto i = indep.begin(); i != indep.end(); i++) {
        for (auto j = indep.begin(); j != indep.end(); j++) {
            if (i == j) continue;
            if (i->first <= j->first && j->second <= i->second) {
                int l = prv[j->first], r = nxt[j->second];
                nxt[l] = r;
                prv[r] = l;
            }
        }
    }

    
    for (pii p: indep) {
        int at;
        for (at = p.first; at != p.second; at = nxt[at])
            printf("%d ", at);
        printf("%d\n", at);
    }
    return 0;
    
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
			string s                  = ")(";
			int L[]                   = {0,0,0,0};
			int R[]                   = {1,1,1,1};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "(())";
			int L[]                   = {0,2};
			int R[]                   = {1,3};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "(((())";
			int L[]                   = {0,2};
			int R[]                   = {1,3};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "(((((((((";
			int L[]                   = {0,2};
			int R[]                   = {1,3};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s                  = "()()()()";
			int L[]                   = {0,0,0,0,2,2,2,4,4,6};
			int R[]                   = {1,3,5,7,3,5,7,5,7,7};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string s                  = ")()(()()((())()()()()()()))(()())()()()(";
			int L[]                   = {3,5,17,25,35};
			int R[]                   = {12,10,30,30,38};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string s                  = ;
			int L[]                   = ;
			int R[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s                  = ;
			int L[]                   = ;
			int R[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string s                  = ;
			int L[]                   = ;
			int R[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ParenthesesDiv1Medium().minSwaps(s, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])));
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
