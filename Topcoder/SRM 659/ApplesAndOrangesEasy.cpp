#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class ApplesAndOrangesEasy {
public:
    int maximumApples(int N, int K, vector <int> info);
};

const int MAXN = 2010;

bool isapple[MAXN];
bool canapple[MAXN];
int q[MAXN];

bool check(int n, int k) {
    int s = 0;
    for(int i=1; i<=k; i++)
        if(isapple[i])
            s++;
    if(s > k/2) return 0;
    for(int i=k+1; i<=n; i++) {
        if(isapple[i - k]) s--;
        if(isapple[i]) s++;
        if(s > k/2) return 0;
    }
    return 1;
}

int ApplesAndOrangesEasy::maximumApples(int N, int K, vector <int> info) {
    int n = N, k = K;
    for(int i=1; i<=n; i++) {
        isapple[i] = 0;
        canapple[i] = 1;
        q[i] = 0;
    }
    for(int x: info) isapple[x] = 1;
    for(int i = 1; i <= n; i++)
        if(isapple[i])
            for(int j = max(1, i - k + 1); j <= min(n, i + k - 1); j++)
                q[j]++;
    
    for(int i = 1; i <= n; ++i) {
        if(isapple[i]) continue;
        isapple[i] = 1;
        if(!check(n, k)) isapple[i] = 0;
    }

    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(isapple[i])
            ans++;
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
            int N                     = 3;
            int K                     = 2;
            int info[]                = {};
            int expected__            = 2;

            clock_t start__           = clock();
            int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 1: {
            int N                     = 10;
            int K                     = 3;
            int info[]                = {3, 8};
            int expected__            = 2;

            clock_t start__           = clock();
            int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 2: {
            int N                     = 9;
            int K                     = 4;
            int info[]                = {1, 4};
            int expected__            = 5;

            clock_t start__           = clock();
            int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 3: {
            int N                     = 9;
            int K                     = 4;
            int info[]                = {2, 4};
            int expected__            = 4;

            clock_t start__           = clock();
            int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 4: {
            int N                     = 23;
            int K                     = 7;
            int info[]                = {3, 2, 9, 1, 15, 23, 20, 19};
            int expected__            = 10;

            clock_t start__           = clock();
            int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }

            // custom cases

/*      case 5: {
        int N                     = ;
        int K                     = ;
        int info[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
        }*/
/*      case 6: {
        int N                     = ;
        int K                     = ;
        int info[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
        }*/
/*      case 7: {
        int N                     = ;
        int K                     = ;
        int info[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
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
