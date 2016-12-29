#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class HamiltonianConstruction {
public:
    vector <string> construct(int k);
};

vector <string> HamiltonianConstruction::construct(int k) {

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
			int k                     = 1;
			string expected__[]       = {"NY", "NN" };

			clock_t start__           = clock();
			vector <string> received__ = HamiltonianConstruction().construct(k);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int k                     = 3;
			string expected__[]       = {"NYYNY", "YNYYY", "YYNYY", "YNYNY", "YYYYN" };

			clock_t start__           = clock();
			vector <string> received__ = HamiltonianConstruction().construct(k);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int k                     = 720;
			string expected__[]       = {"NYYYYYYY", "YNYYYYYY", "YYNYYYYY", "YYYNYYYY", "YYYYNYYY", "YYYYYNYY", "YYYYYYNY", "YYYYYYYN" };

			clock_t start__           = clock();
			vector <string> received__ = HamiltonianConstruction().construct(k);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int k                     = 288;
			string expected__[]       = {"NYYYYNYY", "YNYYYYYY", "YYNYYYNY", "YYYNYYYY", "YNYYNYYY", "YYYYYNYN", "YYNYYYNY", "YYYYYNNN" };

			clock_t start__           = clock();
			vector <string> received__ = HamiltonianConstruction().construct(k);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int k                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = HamiltonianConstruction().construct(k);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int k                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = HamiltonianConstruction().construct(k);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int k                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = HamiltonianConstruction().construct(k);
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
