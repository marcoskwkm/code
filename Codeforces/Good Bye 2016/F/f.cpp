#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 200;

bool seen[MAXN];
vector<int> adj[MAXN];
int ans;
int rem;

bool read(int v) {
    if (seen[v]) return 0;
    rem--;
    seen[v] = 1;
    printf("? %d\n", v);
    fflush(stdout);
    int k;
    scanf("%d", &k);
    if (k == 0) exit(0);
    for (int i = 0; i < k; i++) {
        int nxt;
        scanf("%d", &nxt);
        adj[v].push_back(nxt);
    }
    if (k == 2) {
        ans = v;
        return 1;
    }
    return 0;
}

pii find_midpoint(int v) {
    int cur = adj[v][0];
    vector<int> path;
    while (1) {
        path.insert(path.begin(), cur);
        if (read(cur)) return pii(0, 0);
        if (adj[cur].size() == 1) break;
        if (seen[adj[cur][0]]) swap(adj[cur][0], adj[cur].back());
        cur = adj[cur][0];
    }
    path.push_back(v);
    cur = adj[v][1];
    while (1) {
        path.push_back(cur);
        if (read(cur)) return pii(0, 0);
        if (adj[cur].size() == 1) break;
        if (seen[adj[cur][0]]) swap(adj[cur][0], adj[cur].back());
        cur = adj[cur][0];
    }
    int height = (path.size() + 1) / 2;
    return pii(path[height - 1], height);
}

int dfs(int v, int depth) {
    // debug("dfs %d %d\n", v, depth);
    if (!seen[v] && rem == 0) return v;
    if (read(v)) return v;
    if (depth == 0) return -1;
    for (int nxt: adj[v]) {
        int got = dfs(nxt, depth - 1);
        if (got != -1) return got;
    }
    return -1;
}    

void solve(int v, int prv, int h, int dist_to_root) {
    while (1) {
        // debug("solving for v = %d (h = %d, dist = %d)\n", v, h, dist_to_root);
        if (read(v)) {
            printf("! %d\n", v);
            fflush(stdout);
            return;
        }
        if (dist_to_root <= 2) {
            int got = dfs(v, dist_to_root);
            printf("! %d\n", got);
            fflush(stdout);
            if (got == -1) abort();
            return;
        }
        int dist_to_leaf = h - dist_to_root - 1;
        // debug("dist to leaf = %d\n", dist_to_leaf);
        int cur = v;
        int prv2 = prv;
        int first = -1;
        // debug("cur = %d, prv2 = %d\n", cur, prv2);
        for (int i = 0; i < dist_to_leaf; i++) {
            // debug("i = %d\n", i);
            int to = -1;
            for (int j = 0; j < (int)adj[cur].size(); j++) {
                if (adj[cur][j] != prv2) {
                    to = adj[cur][j];
                    break;
                }
            }
            if (first == -1) first = to;
            if (read(to)) {
                printf("! %d\n", to);
                fflush(stdout);
                return;
            }
            prv2 = cur;
            cur = to;
        }
        if (adj[cur].size() == 1) {
            for (int i = 0; i < (int)adj[v].size(); i++) {
                if (!seen[adj[v][i]]) {
                    prv = v;
                    v = adj[v][i];
                    break;
                }
            }
        }
        else {
            prv = v;
            v = first;
        }
        dist_to_root--;
    }
}            

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        rem = 16;
        memset(seen, 0, sizeof(seen));
        for (int i = 0; i < MAXN; i++)
            adj[i].clear();
        ans = -1;
        int h;
        scanf("%d", &h);
        if (h == 0) return 0;
        int v = 1;
        if (read(v)) {
            printf("! %d\n", ans);
            fflush(stdout);
            continue;
        }
        int dist_to_root;
        int prv = v;
        if (adj[v].size() == 1) {
            dist_to_root = h - 2;
            v = adj[v][0];
        }
        else {
            pii p = find_midpoint(v);
            // debug("midpoint = %d, %d\n", p.first, p.second);
            if (ans != -1) {
                printf("! %d\n", ans);
                fflush(stdout);
                continue;
            }
            dist_to_root = h - p.second - 1;
            for (int nxt: adj[p.first]) {
                // debug("nxt = %d, seen = %d\n", nxt, seen[nxt]);
                if (!seen[nxt]) {
                    v = nxt;
                    break;
                }
            }
            prv = p.first;
        }
        solve(v, prv, h, dist_to_root);
    }
    return 0;
}
