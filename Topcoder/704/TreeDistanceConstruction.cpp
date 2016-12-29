#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

class TreeDistanceConstruction {
public:
    vector <int> construct(vector <int> d);
};

vector<int> q[MAXN];
int id[MAXN];

vector <int> TreeDistanceConstruction::construct(vector <int> d) {
    int n = d.size();
    memset(q, 0, sizeof(q));
    memset(id, -1, sizeof(id));
    for (int i = 0; i < n; i++)
        q[i].clear();
    int longest = 0;
    for (int i = 0; i < n; i++) {
        q[d[i]].push_back(i);
        longest = max(longest, d[i]);
    }
    if (q[longest].size() < 2) return vector<int>();
    int l = q[longest].back();
    q[longest].pop_back();
    int r = q[longest].back();
    q[longest].pop_back();
    vector<int> ans;
    for (int dist = longest - 1; 2 * dist >= longest; dist--) {
        if (2 * dist == longest) {
            if (q[dist].size() < 1) return vector<int>();
            int v = q[dist].back();
            q[dist].pop_back();
            id[dist + 1] = v;
            ans.push_back(l);
            ans.push_back(v);
            ans.push_back(r);
            ans.push_back(v);
            l = r = v;
        }
        else {
            if (q[dist].size() < 2) return vector<int>();
            int u = q[dist].back();
            q[dist].pop_back();
            int v = q[dist].back();
            q[dist].pop_back();
            id[dist + 1] = u;
            ans.push_back(l);
            ans.push_back(u);
            ans.push_back(r);
            ans.push_back(v);
            l = u, r = v;
        }
    }
    if (longest & 1) {
        ans.push_back(l);
        ans.push_back(r);
    }
    for (int dist = 1; dist <= longest; dist++) {
        while (q[dist].size() > 0) {
            if (id[dist] == -1) return vector<int>();
            ans.push_back(id[dist]);
            ans.push_back(q[dist].back());
            q[dist].pop_back();
        }
    }
    if (ans.size() != 2 * (n - 1)) return vector<int>();
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
			int d[]                   = {3,2,2,3};
			int expected__[]          = {1, 2, 1, 0, 2, 3 };

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int d[]                   = {1,2,2,2};
			int expected__[]          = {0, 1, 0, 2, 0, 3 };

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int d[]                   = {1,1,1,1};
			int expected__[]          = { };

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int d[]                   = {1,1,1};
			int expected__[]          = { };

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int d[]                   = {1,1};
			int expected__[]          = {0, 1 };

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

      case 5: {
          int d[]                   = {4, 3, 2, 2, 3, 4};
          int expected__[]          = {};

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
/*      case 6: {
			int d[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int d[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TreeDistanceConstruction().construct(vector <int>(d, d + (sizeof d / sizeof d[0])));
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
