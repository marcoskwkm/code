#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr, x);

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXN = 2010;

int x[MAXN], y[MAXN], r[MAXN];
int energy[MAXN][2];
int n;

bool is_root[MAXN];
vector<int> adj[MAXN];

vector<int> ancestors[MAXN];
int val[MAXN][MAXN];
int opt[MAXN];
int last_opt[MAXN];
int ancestors_taken[MAXN];
int blocked[MAXN];
int done[MAXN];

inline int sq(int k) { return k * k; }

void dfs(int i, vector<int> &anc) {
    ancestors[i] = anc;
    anc.push_back(i);
    for (int nxt: adj[i])
        dfs(nxt, anc);
    anc.pop_back();
}

void increment(int i) {
    ancestors_taken[i]++;
    if (last_opt[i] == ancestors_taken[i])
        for (int a: ancestors[i])
            blocked[a]++;
    for (int nxt: adj[i])
        increment(nxt);
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d%d", &x[i], &y[i], &r[i], &energy[i][0], &energy[i][1]);
            adj[i].clear();
        }

        for (int i = 0; i < n; i++) {
            int prv = -1;
            int rmin = INF;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (r[i] < r[j] && sq(x[i] - x[j]) + sq(y[i] - y[j]) < sq(r[j])) {
                    if (r[j] < rmin) {
                        rmin = r[j];
                        prv = j;
                    }
                }
            }
            if (prv == -1) is_root[i] = 1;
            else {
                is_root[i] = 0;
                adj[prv].push_back(i);
            }
        }

        // find number of ancestors
        vector<int> foo;
        for (int i = 0; i < n; i++)
            if (is_root[i])
                dfs(i, foo);

        int ans = 0;
        for (int i = 0; i < n; i++) {
            opt[i] = 0;
            for (int q = 0; q <= (int)ancestors[i].size(); q++) {
                val[i][q] = (q + 1)/2 * energy[i][0] + q/2 * energy[i][1];
                opt[i] = max(opt[i], val[i][q]);
                if (val[i][q] == opt[i]) last_opt[i] = q;
            }
            ans += opt[i];
        }

        for (int i = 0; i < n; i++)
            if (last_opt[i] == 0)
                for (int a: ancestors[i])
                    blocked[a]++;
                    
        memset(ancestors_taken, 0, sizeof(ancestors_taken));
        memset(done, 0, sizeof(done));
        vector<int> sol;
        for (int step = 0; step < n; step++) {
            bool found = 0;
            for (int i = 0; i < n; i++) {
                if (done[i] || blocked[i]) continue;
                if (opt[i] == val[i][ancestors_taken[i]]) {
                    sol.push_back(i);
                    if (ancestors_taken[i] == last_opt[i])
                        for (int a: ancestors[i])
                            blocked[a]--;
                    done[i] = 1;
                    increment(i);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("fuck %d\n", step);
        }        
        printf("ans = %d\n", ans);
        for (int i = 0; i < n; i++) printf("%d ", sol[i] + 1);
        printf("\n");
    }        
    return 0;
}
   
