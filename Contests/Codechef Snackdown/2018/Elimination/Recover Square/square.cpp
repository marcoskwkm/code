// TL

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210;

vector<int> adj[MAXN * MAXN];
vector<int> cyc_adj[MAXN * MAXN];
bool in_cycle[MAXN * MAXN];
bool solved[MAXN * MAXN];
int sol[MAXN][MAXN];
set<pii> s_edges;

int ans_cnt[MAXN];

int count_inter(int u, int v) {
    int cnt = 0;
    int i = 0;
    for (int w: adj[u]) {
        while (i < (int)adj[v].size() && adj[v][i] < w) i++;
        if (i < (int)adj[v].size() && adj[v][i] == w && in_cycle[w]) cnt++;
    }
    return cnt;
}

inline bool neighbors(int u, int v) {
    if (u > v) swap(u, v);
    return s_edges.find(pii(u, v)) != s_edges.end();
}

pii my_edges[15 * MAXN * MAXN];
bool test(int n, const vector<pii> &edges) {
    int q = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            for (int dr = -2; dr <= 2; dr++) {
                for (int dc = -2; dc <= 2; dc++) {
                    int dist = abs(dr) + abs(dc);
                    if (dist == 0 || dist > 2) continue;
                    int rr = r + dr, cc = c + dc;
                    if (rr < 0 || cc < 0 || rr >= n || cc >= n) continue;
                    if (sol[r][c] > sol[rr][cc]) continue;
                    my_edges[q++] = pii(sol[r][c], sol[rr][cc]);
                }
            }
        }
    }

    sort(my_edges, my_edges + q);
    for (int i = 0; i < q; i++)
        if (my_edges[i] != edges[i])
            return 0;
    
    return 1;
}

bool check(const vector<int> &arr, const vector<pii> &edges, int n) {
    int cnt = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            sol[r][c] = arr[cnt++];
    return test(n, edges);
}

int main() {
    for (int s = 1; s < MAXN; s++) {
        int q = 0;
        for (int r = 0; r < s; r++) {
            for (int c = 0; c < s; c++) {
                for (int dr = -2; dr <= 2; dr++) {
                    for (int dc = -2; dc <= 2; dc++) {
                        int dist = abs(dr) + abs(dc);
                        if (dist == 0 || dist > 2) continue;
                        int rr = r + dr, cc = c + dc;
                        if (rr < 0 || cc < 0 || rr >= s || cc >= s) continue;
                        if (pii(r, c) > pii(rr, cc)) continue;
                        q++;
                    }
                }
            }
        }
        ans_cnt[s] = q;
    }
    
    int t;
    for (cin >> t; t--;) {
        int n, m;
        scanf("%d%d", &n, &m);

        memset(in_cycle, 0, sizeof(in_cycle));
        memset(solved, 0, sizeof(solved));
        s_edges.clear();
        for (int v = 1; v <= n * n; v++) {
            adj[v].clear();
            cyc_adj[v].clear();
        }
        
        vector<pii> edges;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            if (u > v) swap(u, v);
            edges.push_back(pii(u, v));
            adj[u].push_back(v);
            adj[v].push_back(u);
            s_edges.insert(pii(u, v));
        }
        sort(edges.begin(), edges.end());
        for (int v = 1; v <= n * n; v++)
            sort(adj[v].begin(), adj[v].end());
        if (ans_cnt[n] != m) {
            printf("-1\n");
            continue;
        }

        if (n <= 3) {
            vector<int> arr;
            for (int v = 1; v <= n * n; v++)
                arr.push_back(v);
            bool ok = 0;
            do {
                if (check(arr, edges, n)) {
                    ok = 1;
                    break;
                }
            } while (next_permutation(arr.begin(), arr.end()));
            if (!ok) {
                printf("-1\n");
            }
            else {
                for (int r = 0; r < n; r++)
                    for (int c = 0; c < n; c++)
                        printf("%d%c", sol[r][c], c + 1 == n ? '\n' : ' ');
            }
            continue;
        }
        
        vector<int> cycle;
        int threshold = 8;
        int corner = -1;
        for (int v = 1; v <= n * n; v++) {
            if ((int)adj[v].size() <= threshold) {
                cycle.push_back(v);
                in_cycle[v] = 1;
                // debug("%d in cycle\n", v);
            }
            if (adj[v].size() == 5) {
                corner = v;
                // debug("corner = %d\n", corner);
            }
        }
        for (int i = 0; i < (int)cycle.size(); i++) {
            for (int j = i + 1; j < (int)cycle.size(); j++) {
                int u = cycle[i], v = cycle[j];
                if (!neighbors(u, v)) continue;
                int inter = count_inter(u, v);
                if (inter == 2) {
                    cyc_adj[u].push_back(v);
                    cyc_adj[v].push_back(u);
                    // debug("(%d, %d)\n", u, v);
                }
            }
        }
        bool ok = 1;
        for (int v: cycle)
            if (cyc_adj[v].size() != 2)
                ok = 0;
        if (!ok) {
            printf("-1!\n");
            continue;
        }
        sol[0][0] = corner;
        solved[corner] = 1;
        int last = -1, cur = corner;
        for (int c = 1; c < n; c++) {
            int nxt_last = cur;
            cur = (cyc_adj[cur][0] != last ? cyc_adj[cur][0] : cyc_adj[cur][1]);
            solved[cur] = 1;
            last = nxt_last;
            if (cur == corner) ok = 0;
            sol[0][c] = cur;
        }
        for (int r = 1; r < n; r++) {
            int nxt_last = cur;
            cur = (cyc_adj[cur][0] != last ? cyc_adj[cur][0] : cyc_adj[cur][1]);
            solved[cur] = 1;
            last = nxt_last;
            if (cur == corner) ok = 0;
            sol[r][n - 1] = cur;
        }
        for (int c = n - 2; c >= 0; c--) {
            int nxt_last = cur;
            cur = (cyc_adj[cur][0] != last ? cyc_adj[cur][0] : cyc_adj[cur][1]);
            solved[cur] = 1;
            last = nxt_last;
            if (cur == corner) ok = 0;
            sol[n - 1][c] = cur;
        }
        for (int r = n - 2; r >= 1; r--) {
            int nxt_last = cur;
            cur = (cyc_adj[cur][0] != last ? cyc_adj[cur][0] : cyc_adj[cur][1]);
            solved[cur] = 1;
            last = nxt_last;
            if (cur == corner) ok = 0;
            sol[r][0] = cur;
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }

        for (int r = 1; r < n - 1; r++) {
            for (int c = 1; c < n - 1; c++) {
                for (int nxt: adj[sol[r - 1][c - 1]])
                    if (!solved[nxt] && neighbors(nxt, sol[r - 1][c])) {
                        solved[nxt] = 1;
                        sol[r][c] = nxt;
                        break;
                    }
            }
        }        

        if (!test(n, edges)) printf("-1\n");
        else {
            for (int r = 0; r < n; r++)
                for (int c = 0; c < n; c++)
                    printf("%d%c", sol[r][c], c + 1 == n ? '\n' : ' ');
        }        
    }        
    return 0;
}
