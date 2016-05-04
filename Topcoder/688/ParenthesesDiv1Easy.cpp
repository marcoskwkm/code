#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class ParenthesesDiv1Easy {
public:
    vector <int> correct(string s);
};

vector <int> ParenthesesDiv1Easy::correct(string s) {
    int n = s.size();
    if (n & 1) return vector<int> {-1};
    int lo = INF, at = -1, cur = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') cur++;
        else {
            cur--;
            if (cur < lo) {
                lo = cur;
                at = i;
            }
        }
    }
    vector<int> ans;
    if (lo < 0) {
        ans.push_back(0);
        ans.push_back(at);
        reverse(s.begin(), s.begin() + at + 1);
        for (int i = 0; i <= at; i++)
            s[i] = int('(') + int(')') - s[i];
    }
    int curh = 0;
    for (char c: s) {
        if (c == '(') curh++;
        else curh--;
        assert(curh >= 0);
    }
    if (curh == 0) return ans;
    cur = curh;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '(') cur--;
        else cur++;
        if (2*cur == curh) {
            ans.push_back(i);
            ans.push_back(n - 1);
            return ans;
        }
    }
//    assert(false);
    return vector<int> {-1};    
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
			string s                  = ")(";
			int expected__[]          = {0, 0, 1, 1 };

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string s                  = "))))))((((((";
			int expected__[]          = {0, 5, 6, 11 };

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string s                  = "))()())()";
			int expected__[]          = {-1 };

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string s                  = ")()(((";
			int expected__[]          = {0, 0, 3, 3, 5, 5 };

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string s                  = "()";
			int expected__[]          = { };

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string s                  = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string s                  = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string s                  = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = ParenthesesDiv1Easy().correct(s);
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
