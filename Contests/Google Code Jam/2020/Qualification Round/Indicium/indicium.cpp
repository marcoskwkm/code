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

int mat[MAXN][MAXN];
int perm[MAXN];
int done[MAXN];
int hardToFindMatrices[MAXN][MAXN][MAXN];

template<class FTYPE> struct FlowGraph {
    struct Edge {
        int v;
        FTYPE cap;
        Edge(int _v, FTYPE _cap) : v(_v), cap(_cap) {}
    };

    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    FlowGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, FTYPE cap) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(v, cap));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(u, 0));
    }
};

template<class FTYPE> struct Dinic {
    vector<int> ptr, dist;
    FlowGraph<FTYPE> &g;

    Dinic(FlowGraph<FTYPE> &_g) : g(_g) {
        ptr.resize(g.V);
        dist.resize(g.V);
    }

    bool bfs(int s, int t) {
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front();
            if (dist[v] == dist[t]) break;
            q.pop();
            for (int i: g.adj[v]) {
                int nxt = g.edges[i].v;
                if (dist[nxt] == -1 && g.edges[i].cap) {
                    dist[nxt] = dist[v] + 1;
                    q.push(nxt);
                }
            }
        }
        return dist[t] != -1;
    }

    FTYPE dfs(int v, int t, FTYPE flow) {
        if (v == t) return flow;
        for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
            int i = g.adj[v][p];
            int nxt = g.edges[i].v;
            if (dist[nxt] == dist[v] + 1 && g.edges[i].cap) {
                FTYPE got = dfs(nxt, t, min(flow, g.edges[i].cap));
                if (got) {
                    g.edges[i].cap -= got;
                    g.edges[i^1].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    FTYPE max_flow(int s, int t) {
        FTYPE ret = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (FTYPE got = dfs(s, t, numeric_limits<FTYPE>::max()))
                ret += got;
        }
        return ret;
    }
};

bool bruteforce(int n, int k, int r = 0, int c = 0) {
    if (c == n) return bruteforce(n, k, r + 1, 0);
    if (r == n) {
        int sum = 0;
        for (int i = 0; i < n; i++) sum += mat[i][i];
        return sum == k;
    }

    for (int val = 1; val <= n; val++) {
        bool ok = 1;
        for (int pr = 0; pr < r; pr++)
            if (mat[pr][c] == val)
                ok = 0;
        for (int pc = 0; pc < c; pc++)
            if (mat[r][pc] == val)
                ok = 0;
        if (!ok) continue;
        mat[r][c] = val;
        if (bruteforce(n, k, r, c + 1)) return 1;
        mat[r][c] = 0;
    }

    return 0;
}

void swapAll(int n, int x, int y) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (mat[r][c] == x) mat[r][c] = y;
            else if (mat[r][c] == y) mat[r][c] = x;
        }
    }
}

void getHardToFindMatrix(int n) { // at least for me =P
    if (done[n]) {
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                mat[r][c] = hardToFindMatrices[n][r][c];
        return;
    }

    mat[0][0] = 2, mat[0][1] = 1;
    for (int c = 2; c < n; c++)
        mat[0][c] = c + 1;
    mat[1][0] = 1, mat[1][1] = 2;
    for (int c = 2; c < n; c++)
        mat[1][c] = 3 + (c - 1) % (n - 2);

    for (int r = 2; r < n; r++) {
        FlowGraph<int> g(2 * n + 2);
        int s = 2 * n, t = 2 * n + 1;

        for (int val = 1; val <= n; val++) {
            g.add_edge(s, val - 1, 1);
            g.add_edge(n + val - 1, t, 1);
            for (int c = 0; c < n; c++) {
                bool ok = 1;
                for (int rr = 0; rr < r; rr++)
                    if (mat[rr][c] == val)
                        ok = 0;
                if (ok) g.add_edge(c, n + val - 1, 1);
            }
        }

        Dinic<int> dinic(g);
        assert(dinic.max_flow(s, t) == n);

        for (int c = 0; c < n; c++) {
            for (int idx: g.adj[c]) {
                if (g.edges[idx].v != s && g.edges[idx].cap == 0) {
                    mat[r][c] = g.edges[idx].v - n + 1;
                }
            }
        }
    }

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            hardToFindMatrices[n][r][c] = mat[r][c];
    done[n] = 1;
}

int main() {
    int n, k, t = 1, T;
    for (cin >> T; t <= T; t++) {
        cin >> n >> k;
        printf("Case #%d: ", t);

        for (int val = 1; val <= n; val++) perm[val] = val;

        bool flip = 0;
        if (k > n * n + n - k) {
            k = n * n + n - k;
            flip = 1;
        }

        if (k == n + 1 || (n == 3 && k == 5)) {
            printf("IMPOSSIBLE\n");
            continue;
        }

        printf("POSSIBLE\n");
        memset(mat, 0, sizeof(mat));
        if (n <= 3) {
            bruteforce(n, k);
        } else {
            if (k % n == 0) {
                for (int r = 0; r < n; r++) {
                    for (int c = 0; c < n; c++) {
                        mat[r][c] = 1 + (r - c + n) % n;
                    }
                }
                int d = k / n;
                swap(perm[1], perm[d]);
            } else {
                int x = max(1, (k - n - 3) / (n - 2));
                int rem = k - (n - 2) * x;
                int y = rem / 2;
                if (y == x || rem - y == x) y--;
                assert(1 <= y && y <= n && 1 <= rem - y && rem - y <= n);

                if (y != rem - y) {
                    for (int r = 0; r < n; r++) {
                        for (int c = 0; c < n; c++) {
                            mat[r][c] = 1 + (r - c + n) % n;
                        }
                    }
                    for (int c = 0; c < n; c++) {
                        swap(mat[0][c], mat[1][c]);
                    }
                    swap(perm[1], perm[x]);
                    swap(perm[2], perm[y]);
                    swap(perm[n], perm[rem - y]);
                } else {
                    getHardToFindMatrix(n);
                    for (int c = 2; c < n; c++) {
                        int idx = -1;
                        for (int r = 2; r < n; r++) {
                            if (mat[r][c] == 1)
                                idx = r;
                        }
                        for (int i = 0; i < n; i++) {
                            swap(mat[c][i], mat[idx][i]);
                        }
                    }
                    swap(perm[1], perm[x]);
                    swap(perm[2], perm[y]);
                }
            }
        }

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                printf("%d ", flip ? (n + 1 - perm[mat[r][c]]) : perm[mat[r][c]]);
            }
            printf("\n");
        }
    }
    return 0;
}
