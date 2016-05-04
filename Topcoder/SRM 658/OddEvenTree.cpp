#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class OddEvenTree {
public:
    vector <int> getTree(vector <string> x);
};

const int MAXN = 100;

vector<int> dist[MAXN];
vector<int> ans;
bool foi[MAXN];
int n;

void dfs(int v) {
    foi[v] = 1;
    for(int nxt=0; nxt<n; ++nxt) {
        if(foi[nxt] || dist[v][nxt] == 0) continue;
        ans.push_back(v);
        ans.push_back(nxt);
        dfs(nxt);
    }
}

vector <int> OddEvenTree::getTree(vector <string> x) {
    n = x.size();
    ans.clear();
    memset(foi,0,sizeof(foi));
    for(int r=0; r<n; ++r) {
        dist[r].clear();
        for(char c: x[r])
            dist[r].push_back(c == 'O');
    }
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
                if((dist[i][j]^dist[j][k]) != dist[i][k])
                    return vector<int>(1,-1);
    dfs(0);
    for(int v=0; v<n; ++v)
        if(!foi[v])
            return vector<int>(1,-1);
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
            string x[]                = {"EOE",
                                         "OEO",
                                         "EOE"};
            int expected__[]          = {0, 1, 2, 1 };

            clock_t start__           = clock();
            vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 1: {
            string x[]                = {"EO",
                                         "OE"};
            int expected__[]          = {0, 1 };

            clock_t start__           = clock();
            vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 2: {
            string x[]                = {"OO",
                                         "OE"};
            int expected__[]          = {-1 };

            clock_t start__           = clock();
            vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 3: {
            string x[]                = {"EO",
                                         "EE"};
            int expected__[]          = {-1 };

            clock_t start__           = clock();
            vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 4: {
            string x[]                = {"EOEO",
                                         "OEOE",
                                         "EOEO",
                                         "OEOE"};
            int expected__[]          = {0, 1, 0, 3, 2, 1 };

            clock_t start__           = clock();
            vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
            return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }

            // custom cases

/*      case 5: {
        string x[]                = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
        return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 6: {
        string x[]                = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
        return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 7: {
        string x[]                = ;
        int expected__[]          = ;

        clock_t start__           = clock();
        vector <int> received__   = OddEvenTree().getTree(vector <string>(x, x + (sizeof x / sizeof x[0])));
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
