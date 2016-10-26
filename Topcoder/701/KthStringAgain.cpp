#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<char, int, lint> tcil;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class KthStringAgain {
public:
    string getKth(string s, long long k);
};

string KthStringAgain::getKth(string s, long long k) {
    vector<string> vs;
    k = (k + 1) / 2;
    int n = s.size();
    string ans = s;
    for (int l = 0; l < n; l++) {
        if (k == 1 && (int)s.size() > 0) {
            ans[l] = s[0];
            s.erase(s.begin());
            continue;
        }
        debug("rem: %s (k = %lld)\n", s.c_str(), k);
        vector<tcil> vp;
        lint q = (1 << (max<int>(0, s.size() - 2)));
        for (int i = 0; i < (int)s.size(); i++) {
            vp.push_back(tcil(s[i], i, q));
            q = max(1ll, q / 2);
        }
        vector<int> trash;
        sort(vp.begin(), vp.end());
            
        for (tcil t: vp) {
            char c;
            lint qq;
            int i;
            tie(c, i, qq) = t;
            debug("seeing %c: q = %lld\n", c, qq);
            if (k > qq) k -= qq;
            else {
                ans[l] = c;
                trash.push_back(i);
                break;
            }
        }
        sort(trash.begin(), trash.end(), greater<int>());
        for (int i: trash)
            s.erase(s.begin() + i);
        reverse(s.begin(), s.end());
    }
    return ans;
    
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        string ss = s;
        for (int i = 0; i < n - 1; i++)
            if (mask & (1 << i))
                reverse(ss.end() - i - 2, ss.end());
        vs.push_back(ss);
    }
    sort(vs.begin(), vs.end());
    for (string x: vs) printf("%s\n", x.c_str());
    return "";  
    
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
			string s                  = "xyz";
			long long k               = 5;
			string expected__         = "yzx";

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "abc";
			long long k               = 1;
			string expected__         = "abc";

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "abc";
			long long k               = 8;
			string expected__         = "cba";

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "topcoder";
			long long k               = 58;
			string expected__         = "ooredcpt";

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s                  = "aaaabcdeeeghhhhhiijjjkllmmooooqqrrrrssttuuvvvvvwyy";
			long long k               = 38517901796974LL;
			string expected__         = "aaaacdeehhhijklmmqqrsttvvvvwyyvuusrrrooooljjihhgeb";

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			string s                  = "barco";
			long long k               = 12;
			string expected__         = "";

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			string s                  = ;
			long long k               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s                  = ;
			long long k               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = KthStringAgain().getKth(s, k);
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
