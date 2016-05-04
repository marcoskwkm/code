#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class ColorfulGarden {
public:
    vector <string> rearrange(vector <string> garden);
};

int cnt[300];

vector <string> ColorfulGarden::rearrange(vector <string> garden) {
    int n = garden[0].size();
    vector<char> v;
    for (string s: garden) {
        for (char c: s) {
            v.push_back(c);
            cnt[c]++;
            if (cnt[c] > n) return vector<string>{};
        }
    }
    sort(v.begin(), v.end(), [](char a, char b) {
        if (cnt[a] != cnt[b]) return cnt[a] < cnt[b];
        return a > b;
    });
    vector<string> ans = garden;
    for (int i = 0; i < n; i++) {
        ans[i&1][i] = v.back();
        v.pop_back();
    }
    for (int i = 0; i < n; i++) {
        ans[(i&1)^1][i] = v.back();
        v.pop_back();
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
	template<> ostream& operator<<(ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, clock_t elapsed) { 
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
			string garden[]           = {"aa",
 "bb"};
			string expected__[]       = {"ab", "ba" };

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string garden[]           = {"xxxx",
 "xxxx"};
			string expected__[]       = { };

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string garden[]           = {"abcd",
 "abcd"};
			string expected__[]       = {"abcd", "dcba" };

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string garden[]           = {"abcdefghijklm",
 "nopqrstuvwxyz"};
			string expected__[]       = {"abcdefghijklm", "nopqrstuvwxyz" };

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string garden[]           = {"aaa",
 "aab"};
			string expected__[]       = { };

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string garden[]           = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string garden[]           = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string garden[]           = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = ColorfulGarden().rearrange(vector <string>(garden, garden + (sizeof garden / sizeof garden[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
