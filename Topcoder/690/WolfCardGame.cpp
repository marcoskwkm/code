#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class WolfCardGame {
public:
    vector <int> createAnswer(int N, int K);
};

vector <int> WolfCardGame::createAnswer(int N, int K) {
    N = 60, K = 15;
    vector<int> ret;
    int d;
    for (int i = 2; i; i++)
        if (N % i != 0) {
            d = i;
            break;
        }
    int cnt= 0;
    for (int i = 1; i <= 100 && cnt < K; i++)
        if (i % d == 0)
            ret.push_back(i), cnt++;
    return ret;
    
}
    
//     vector<int> easy = {2, 3, 5};    
//     for (int p: easy) {
//         if (N % p) {
//             vector<int> ans;
//             for (int i = 1; i <= K; i++)
//                 ans.push_back(i*p);
//             return ans;
//         }
//     }
// //    assert (N == 30 || N == 60 || N == 90);
//     vector<int> ans = {N == 90 ? 2 : 1};
//     for (int i = 1; i <= K - 1; i++)
//         ans.push_back(7 * i);
//     return ans;
//}

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
            int N                     = 20;
            int K                     = 4;
            int expected__[]          = {1, 2, 3, 4 };

            clock_t start__           = clock();
            vector <int> received__   = WolfCardGame().createAnswer(N, K);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 1: {
            int N                     = 40;
            int K                     = 1;
            int expected__[]          = {39 };

            clock_t start__           = clock();
            vector <int> received__   = WolfCardGame().createAnswer(N, K);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 2: {
            int N                     = 97;
            int K                     = 6;
            int expected__[]          = {7, 68, 9, 10, 62, 58 };

            clock_t start__           = clock();
            vector <int> received__   = WolfCardGame().createAnswer(N, K);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 3: {
            int N                     = 2;
            int K                     = 12;
            int expected__[]          = {33, 69, 42, 45, 96, 15, 57, 12, 93, 9, 54, 99 };

            clock_t start__           = clock();
            vector <int> received__   = WolfCardGame().createAnswer(N, K);
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }

            // custom cases

/*      case 4: {
        int N                     = ;
        int K                     = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = WolfCardGame().createAnswer(N, K);
        return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 5: {
        int N                     = ;
        int K                     = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = WolfCardGame().createAnswer(N, K);
        return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 6: {
        int N                     = ;
        int K                     = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = WolfCardGame().createAnswer(N, K);
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
