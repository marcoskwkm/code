#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55;
const int MAXR = 110;

int R, C;
char grid[MAXN][MAXN];
vector<int> adj[2 * MAXR];
int ray_id[MAXN][MAXN];
int cmp_id[MAXN][MAXN][2]; // 0 - hor, 1 - ver
int dr[] = {0, -1, 0, 1};
int dc[] = {1, 0, -1, 0};
vector<pii> rays[2 * MAXN * MAXN];
int neg[2* MAXR];
int indeg[2 * MAXR];
vector<int> cmp[2 * MAXR];
int value[2 * MAXR];

void dfs(int r, int c, int d, int id) {
    if (r < 0 || c < 0 || r >= R || c >= C || grid[r][c] == '#' || cmp_id[r][c][d % 2] != -1)
        return;
    cmp_id[r][c][d % 2] = id;
    if (grid[r][c] == '|' || grid[r][c] == '-')
        rays[id].push_back(pii(ray_id[r][c], d % 2));
    int nr = r + dr[d], nc = c + dc[d];
    if (nr < 0 || nc < 0 || nr >= R || nc >= C || grid[nr][nc] == '#')
        return;
    if (grid[nr][nc] == '/') {
        if (d == 0) dfs(nr - 1, nc, 1, id);
        else if (d == 1) dfs(nr, nc + 1, 0, id);
        else if (d == 2) dfs(nr + 1, nc, 3, id);
        else if (d == 3) dfs(nr, nc - 1, 2, id);
    }
    else if (grid[nr][nc] == '\\') {
        if (d == 0) dfs(nr + 1, nc, 3, id);
        else if (d == 1) dfs(nr, nc - 1, 2, id);
        else if (d == 2) dfs(nr - 1, nc, 1, id);
        else if (d == 3) dfs(nr, nc + 1, 0, id);
    }
    else {
        dfs(nr, nc, d, id);
    }
}

set<pii> foi;
void add_edge(int u, int v) {
    if (foi.find(pii(u, v)) != foi.end()) return;
    foi.insert(pii(u, v));
    adj[u].push_back(v);
}

namespace Tarjan {
    int cmp[2 * MAXR]; // component of [i]
    int cnt;       // number of components
    int ind[2 * MAXR], low[2 * MAXR], pre;
    bool instack[2 * MAXR];
    stack<int> st;

    void tarjan(int v) {
        ind[v] = low[v] = pre++;
        st.push(v);
        instack[v] = 1;
        for (int nxt: adj[v]) {
            if (ind[nxt] == -1) {
                tarjan(nxt);
                low[v] = min(low[v], low[nxt]);
            }
            else if (instack[nxt]) low[v] = min(low[v], ind[nxt]);
        }
        if (ind[v] == low[v]) {
            int vv;
            do {
                vv = st.top();
                st.pop();
                instack[vv] = 0;
                cmp[vv] = cnt;
            } while (vv != v);
            ++cnt;
        }
    }

    inline void init() {
        memset(ind, -1, sizeof(ind));
        pre = 0; cnt = 0;
    }
}

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        foi.clear();
        for (int i = 0; i < 2 * MAXN * MAXN; i++)
            rays[i].clear();
        scanf("%d%d", &R, &C);
        int n_rays = 0;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == '|' || grid[r][c] == '-')
                    ray_id[r][c] = n_rays++;
            }
        }
        memset(cmp_id, -1, sizeof(cmp_id));
        int n_cmp = 0;
        bool ok = 1;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == '#') continue;
                if (cmp_id[r][c][0] == -1) {
                    dfs(r, c, 0, n_cmp);
                    dfs(r, c - 1, 2, n_cmp++);
                    if (rays[cmp_id[r][c][0]].size() > 1) {
                        for (pii p: rays[cmp_id[r][c][0]])
                            add_edge(2*p.first + p.second, 2*p.first + (1 - p.second));
                    }                    
                }
                if (cmp_id[r][c][1] == -1) {
                    dfs(r, c, 1, n_cmp);
                    dfs(r - 1, c, 3, n_cmp++);
                    if (rays[cmp_id[r][c][1]].size() > 1) {
                        for (pii p: rays[cmp_id[r][c][1]])
                            add_edge(2*p.first + p.second, 2*p.first + (1 - p.second));
                    }
                }
                int ch = cmp_id[r][c][0], cv = cmp_id[r][c][1];
                debug("(%d, %d): %d(%d) %d(%d)\n", r, c, ch, rays[ch].size(), cv, rays[cv].size());
                if (rays[ch].size() == 1 && rays[cv].size() == 1) {
                    pii rh = rays[ch][0], rv = rays[cv][0];
                    add_edge(2*rh.first + (1 - rh.second), 2*rv.first + rv.second);
                    add_edge(2*rv.first + (1 - rv.second), 2*rh.first + rh.second);
                }
                else if (rays[ch].size() == 1) {
                    pii rh = rays[ch][0];
                    add_edge(2*rh.first + (1 - rh.second), 2*rh.first + rh.second);
                }
                else if (rays[cv].size() == 1) {
                    pii rv = rays[cv][0];
                    add_edge(2*rv.first + (1 - rv.second), 2*rv.first + rv.second);
                }
                else if (grid[r][c] == '.') {
                    debug("fail %d %d\n", r, c);
                    ok = 0;
                }
            }
        }
        Tarjan::init();
        for (int ray = 0; ray < 2*n_rays; ray++)
            if (Tarjan::ind[ray] == -1)
                Tarjan::tarjan(ray);
        for (int ray = 0; ray < n_rays; ray++) {
            if (Tarjan::cmp[2*ray] == Tarjan::cmp[2*ray + 1]) {
                ok = 0;
                break;
            }
            neg[Tarjan::cmp[2*ray]] = Tarjan::cmp[2*ray + 1];
            neg[Tarjan::cmp[2*ray + 1]] = Tarjan::cmp[2*ray];
        }
        if (!ok) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        printf("POSSIBLE\n");
        for (int r = 0; r < 2*n_rays; r++) {
            cmp[Tarjan::cmp[r]].push_back(r);
            for (int nxt: adj[r])
                if (Tarjan::cmp[r] != Tarjan::cmp[nxt])
                    indeg[Tarjan::cmp[nxt]]++;
        }
        vector<int> topsort;
        for (int i = 0; i < Tarjan::cnt; i++) {
            if (indeg[i] == 0)
                topsort.push_back(i);
        }
        memset(value, -1, sizeof(value));
        for (int v: topsort) {
            for (int r: cmp[v]) {
                for (int nxt: adj[r]) {
                    if (Tarjan::cmp[r] != Tarjan::cmp[nxt]) {
                        if (--indeg[Tarjan::cmp[nxt]] == 0) {
                            topsort.push_back(Tarjan::cmp[nxt]);
                        }
                    }
                }
            }
            if (value[v] == -1) {
                value[v] = 0;
                value[neg[v]] = 1;
            }
        }
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] != '-' && grid[r][c] != '|')
                    printf("%c", grid[r][c]);
                else {
                    if (value[Tarjan::cmp[ray_id[r][c]]] == 1)
                        printf("|");
                    else printf("-");
                }
            }
            printf("\n");
        }
    }        
    return 0;
}
