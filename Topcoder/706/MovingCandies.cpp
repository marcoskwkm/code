#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class MovingCandies {
public:
    int minMoved(vector <string> t);
};

const int MAXD = 25;

int dp[MAXD][MAXD][MAXD*MAXD];
char grid[MAXD][MAXD];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int n, m;

int go(int r, int c, int k) {
    if (k < 0) return INF;
    if (dp[r][c][k] != -1) return dp[r][c][k];
    int ret = (grid[r][c] == '.');
    if (r == 0 && c == 0) return ret;
    int add = INF;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >= n || nc >= m)
            continue;
        add = min(add, go(nr, nc, k - 1));
    }
    return dp[r][c][k] = ret + add;
}    

int MovingCandies::minMoved(vector <string> t) {
    n = t.size(), m = t[0].size();
    int total = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++){
            if (t[r][c] == '#')
                total++;
            grid[r][c] = t[r][c];
        }
    }
    if (total < n + m - 1) return -1;
    memset(dp, -1, sizeof(dp));
    return go(n - 1, m - 1, total - 1);
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
            string t[]                = {
                "#...###",
                "#...#.#",
                "##..#.#",
                ".#....#"
            };
            int expected__            = 3;

            clock_t start__           = clock();
            int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 1: {
            string t[]                = {
                "#...###",
                "#...#.#",
                "##..###",
                ".#....#"
            };
            int expected__            = 2;

            clock_t start__           = clock();
            int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 2: {
            string t[]                = {
                ".#..",
                "##..",
                "..#.",
                "..#.",
                "..##",
                "..##"
            };
            int expected__            = 2;

            clock_t start__           = clock();
            int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 3: {
            string t[]                = {
                ".....",
                ".###.",
                "####.",
                "....."
            };
            int expected__            = -1;

            clock_t start__           = clock();
            int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 4: {
            string t[]                = {
                ".#...#.###.#",
                "#.#.##......",
                ".#.#......#.",
                "..#.......#.",
                "##.........."
            };
            int expected__            = 9;

            clock_t start__           = clock();
            int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 5: {
            string t[]                = {
                "###.#########..#####",
                ".#######.###########"
            };
            int expected__            = 0;

            clock_t start__           = clock();
            int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }
        case 6: {
            string t[]                = {
                "..",
                ".."
            };
            int expected__            = -1;

            clock_t start__           = clock();
            int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
            return verify_case(casenum__, expected__, received__, clock()-start__);
        }

            // custom cases

      case 7: {
          string t[]                = {
              "#.##.##",
              "#.#...#",
              "###...#",
              "......#",
              "......#"
          };
        int expected__            = 0;

        clock_t start__           = clock();
        int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
        }
/*      case 8: {
        string t[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
        }*/
/*      case 9: {
        string t[]                = ;
        int expected__            = ;

        clock_t start__           = clock();
        int received__            = MovingCandies().minMoved(vector <string>(t, t + (sizeof t / sizeof t[0])));
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
