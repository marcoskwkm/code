#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class CampLunch {
public:
    int count(int N, int M, vector <string> a);    
};

const int MAXN = 20;

int blocked[MAXN][MAXN];
vector<string> mat;
int n, m;

vector<int> pairs[MAXN][MAXN];

int go(int i) {
    if(i == m) return 1;
    for(int mask = 0; mask < (1<<m); ++mask) {
        bool ok = 1;
        for(int d=0; d<m; d++) {
            if(blocked[i][d] && (mask&(1<<d)) == 0) {
                ok = 0;
                break;
            }
        }
        if(!ok) continue;
        int cnt = 0;
        lint ret = 0;
        for(int d=0; d<m; ++d) {
            if(mask&(1<<d)) {
                



int CampLunch::count(int N, int M, vector <string> a) {
    memset(blocked, 0, sizeof(blocked));
    n = N; m = M;
    mat = a;
    for(int a=0; a<n; ++a)
        for(int b=0; b<m; ++b)
            pairs[a][b].clear();
    for(int d=0; d<n; ++d) {
        for(int i=0; i+1<m; i++) {
            int cur = mat[d][i] - 'A';
            int nxt = mat[d][i+1] = 'A';
            pairs[d][cur].push_back(nxt);
            pairs[d][nxt].push_back(cur);
        }
    }
    return go(0);
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
            int N                     = 2;
            int M                     = 2;
            string a[]                = {"AB","AB"};
            int expected__            = 7;

            clock_t start__           = clock();
            int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 1: {
            int N                     = 2;
            int M                     = 3;
            string a[]                = {"ABC","ABC"};
            int expected__            = 22;

            clock_t start__           = clock();
            int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 2: {
            int N                     = 2;
            int M                     = 3;
            string a[]                = {"ABC","BAC"};
            int expected__            = 21;

            clock_t start__           = clock();
            int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 3: {
            int N                     = 1;
            int M                     = 1;
            string a[]                = {"A"};
            int expected__            = 1;

            clock_t start__           = clock();
            int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 4: {
            int N                     = 1;
            int M                     = 10;
            string a[]                = {"ABDEFHIGJC"};
            int expected__            = 89;

            clock_t start__           = clock();
            int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 5: {
            int N                     = 16;
            int M                     = 16;
            string a[]                = {"ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP"};
            int expected__            = 950052677;

            clock_t start__           = clock();
            int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }

            // custom cases

/*      case 6: {
        int N                     = ;
        int M                     = ;
        string a[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
        }*/
/*      case 7: {
        int N                     = ;
        int M                     = ;
        string a[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
        }*/
/*      case 8: {
        int N                     = ;
        int M                     = ;
        string a[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = CampLunch().count(N, M, vector <string>(a, a + (sizeof a / sizeof a[0])));
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
