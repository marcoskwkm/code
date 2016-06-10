#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;

class TreeSums {
public:
    long long findSums(int N, int seed, int C, int D);
};

lint tree[4*MAXN];
vector<int> adj[MAXN];
vector<int> cst[MAXN];
lint qn[MAXN];
lint parcost[MAXN];
int parent[MAXN];
int depth[MAXN];
int heavy[MAXN];
int root[MAXN];
int hld_pos[MAXN];
lint sumalldist[MAXN];

void tree_update(int i, int l, int r, int pos, lint val) {
    if (l > pos || r < pos) return;
    if (l == r) {
        tree[i] += val;
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    tree_update(L, l, mid, pos, val); tree_update(R, mid + 1, r, pos, val);
    tree[i] = tree[L] + tree[R];
}

lint tree_query(int i, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[i];
    if (ql > r || qr < l) return 0;
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return tree_query(L, l, mid, ql, qr) + tree_query(R, mid + 1, r, ql, qr);
}

int hld_dfs(int v) {
    int hi = 0, ret = 1;
    qn[v] = 1;
    for (int i = 0; i < (int)adj[v].size(); i++) {
        int nxt = adj[v][i], cost = cst[v][i];        
        if (nxt == parent[v]) {
            parcost[v] = cost;
            continue;
        }
        parent[nxt] = v;
        depth[nxt] = depth[v] + 1;
        int got = hld_dfs(nxt);
        if (got > hi) {
            hi = got;
            heavy[v] = nxt;
        }
        ret += got;
        qn[v] += qn[nxt];
        sumalldist[nxt] += lint(qn[nxt]) * cost;
        sumalldist[v] += sumalldist[nxt];
    }
    return ret;
}

void hld_preprocess(int s, int n) {
    memset(heavy, -1, sizeof(heavy));
    parent[s] = -1; depth[s] = 0;
    hld_dfs(s);
    int cur = 0;
     for (int v = 0; v < n; v++) {
        if (parent[v] == -1 || heavy[parent[v]] != v) {
            for (int j = v; j != -1; j = heavy[j]) {
                root[j] = v, hld_pos[j] = cur++;
            }
        }
    }
    memset(tree, 0, sizeof(tree));
}

lint hld_query(int u, int v, int n) {
    lint ret = 0;
    for (; root[u] != root[v]; v = parent[root[v]]) {
        if (depth[root[u]] > depth[root[v]]) swap(u, v);
        ret += tree_query(0, 0, n-1, hld_pos[root[v]], hld_pos[v]);
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) ret += tree_query(0, 0, n - 1, hld_pos[u] + 1, hld_pos[v]);
    return ret;
}

inline void hld_update(int v, lint val, int n) {
    tree_update(0, 0, n - 1, hld_pos[v], val);
}

lint rdist[MAXN];
int center[MAXN];
lint sumdist[MAXN];

lint go(int v, int n) {
    lint best = LINF, at = -1;
    lint ret = 0;
    for (int i = 0; i < (int)adj[v].size(); i++) {
        int nxt = adj[v][i], cost = cst[v][i];
        if (nxt == parent[v]) continue;
        ret ^= go(nxt, n);
        rdist[center[nxt]] += cost;
        sumdist[center[nxt]] += (sumalldist[v] - lint(qn[v])*parcost[v]) - sumalldist[nxt] + lint(qn[v] - qn[nxt]) * rdist[center[nxt]];
        hld_update(nxt, qn[v] - qn[nxt], n);
        while (center[nxt] != v) {
            int qup = hld_query(0, center[nxt], n);
            if (qup >= qn[center[nxt]]) {
                lint newsumdist = sumdist[center[nxt]] - lint(qup - qn[center[nxt]]) * parcost[center[nxt]];
                lint newrdist = rdist[center[nxt]] - parcost[center[nxt]];
                center[nxt] = parent[center[nxt]];
                sumdist[center[nxt]] = newsumdist;
                rdist[center[nxt]] = newrdist;
            }
            else break;
        }
        if (sumdist[center[nxt]] < best) {
            best = sumdist[center[nxt]];
            at = center[nxt];
        }
    }
    if (at == -1) {
        at = v;
        best = 0;
    }        
    center[v] = at;
    sumdist[v] = best;
    return best ^ ret;
}    

long long TreeSums::findSums(int N, int seed, int C, int D) {
    memset(sumdist, 0, sizeof(sumdist));
    memset(rdist, 0, sizeof(rdist));
    memset(sumalldist, 0, sizeof(sumalldist));
    for (int v = 0; v < N; v++) {
        adj[v].clear();
        cst[v].clear();
    }
    int m1 = (int)1e9, m2 = (int)1e6;
    lint cur = seed;
    for (int i = 0; i < N - 1; i++) {
        cur = (C * cur + D) % m1;
        int u = cur % (i + 1);
        int v = i + 1;
        cur = (C * cur + D) % m1;
        int len = cur % m2;
        adj[u].push_back(v);
        cst[u].push_back(len);
        adj[v].push_back(u);
        cst[v].push_back(len);
    }
    hld_preprocess(0, N);

    return go(0, N);
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
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
			int N                     = 6;
			int seed                  = 8;
			int C                     = 3;
			int D                     = 13;
			long long expected__      = 856320;

			clock_t start__           = clock();
			long long received__      = TreeSums().findSums(N, seed, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 2;
			int seed                  = 10;
			int C                     = 20;
			int D                     = 30;
			long long expected__      = 4630;

			clock_t start__           = clock();
			long long received__      = TreeSums().findSums(N, seed, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 6;
			int seed                  = 55;
			int C                     = 1;
			int D                     = 18;
			long long expected__      = 22;

			clock_t start__           = clock();
			long long received__      = TreeSums().findSums(N, seed, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 300000;
			int seed                  = 999999990;
			int C                     = 999999990;
			int D                     = 999999991;
			long long expected__      = 438628640790LL;

			clock_t start__           = clock();
			long long received__      = TreeSums().findSums(N, seed, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			int seed                  = ;
			int C                     = ;
			int D                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TreeSums().findSums(N, seed, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			int seed                  = ;
			int C                     = ;
			int D                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TreeSums().findSums(N, seed, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int seed                  = ;
			int C                     = ;
			int D                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TreeSums().findSums(N, seed, C, D);
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
