#include <array>
#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int LOG = 20;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T> vector<T> make_vector(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template<class T, class... Args> auto make_vector(size_t head, Args &&...rem) {
    auto inner = make_vector<T>(rem...);
    return vector<decltype(inner)>(head, inner);
}

template<class T, class C = vector<T>> inline void print_array(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class EType> struct Graph {
    int V;
    vector<vector<EType *>> adj;

    Graph(int _V) : V(_V) { adj.resize(V); }
};

struct Edge {
    static const int MAX_EDGES = (int)1e8;
    static int edge_cnt;
    static array<Edge, MAX_EDGES> edges;

    int v;
    bool is_bridge;
    Edge *rev;

    Edge() {}
    Edge(int _v) : v(_v), is_bridge(false), rev(NULL) {}

    static void add(Graph<Edge> &g, int u, int v) {
        edges[edge_cnt++] = Edge(v);
        edges[edge_cnt++] = Edge(u);
        auto uv = &edges[edge_cnt - 2];
        auto vu = &edges[edge_cnt - 1];
        uv->rev = vu;
        vu->rev = uv;
        g.adj[u].push_back(uv);
        g.adj[v].push_back(vu);
    }
};

int Edge::edge_cnt = 0;
array<Edge, Edge::MAX_EDGES> Edge::edges;

void mark_bridges(Graph<Edge> &g) {
    vector<int> ind(g.V, -1), low(g.V);
    int cnt = 0;

    auto dfs = y_combinator([&](auto _dfs, int v, int prv) -> void {
        ind[v] = low[v] = cnt++;
        for (const auto &edge: g.adj[v]) {
            if (ind[edge->v] == -1) {
                _dfs(edge->v, v);
                low[v] = min(low[v], low[edge->v]);
                if (low[edge->v] == ind[edge->v]) {
                    edge->is_bridge = true;
                    edge->rev->is_bridge = true;
                }
            } else if (edge->v != prv) {
                low[v] = min(low[v], ind[edge->v]);
            }
        }
    });

    for (int v = 0; v < g.V; v++) {
        if (ind[v] == -1) {
            dfs(v, -1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        debug("t = %d...\n", t);
        printf("Case #%d: ", t);

        Edge::edge_cnt = 0;

        int N, M;
        cin >> N >> M;
        Graph<Edge> g(N);

        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            Edge::add(g, u - 1, v - 1);
        }

        mark_bridges(g);

        vector<bool> has_odd_cycle;
        vector<int> cmp(N, -1);
        vector<int> color(N);

        auto process_component = y_combinator([&](auto dfs, int v, int c = 0) -> bool {
            cmp[v] = has_odd_cycle.size();
            color[v] = c;
            bool flag = 0;

            for (const auto &edge: g.adj[v]) {
                if (edge->is_bridge) {
                    continue;
                }

                if (cmp[edge->v] != -1) {
                    if (color[edge->v] != (c ^ 1)) {
                        flag = 1;
                    }
                    continue;
                }

                flag = dfs(edge->v, c ^ 1) || flag;
            }

            return flag;
        });

        for (int v = 0; v < N; v++) {
            if (cmp[v] != -1) {
                continue;
            }

            has_odd_cycle.push_back(process_component(v));
        }

        Graph<Edge> contracted(has_odd_cycle.size());

        for (int v = 0; v < N; v++) {
            for (const auto &edge: g.adj[v]) {
                if (edge->is_bridge && v < edge->v) {
                    Edge::add(contracted, cmp[v], cmp[edge->v]);
                }
            }
        }

        vector<int> dist(contracted.V, -1);
        queue<int> q;

        for (int v = 0; v < contracted.V; v++) {
            if (has_odd_cycle[v]) {
                dist[v] = 0;
                q.push(v);
            }
        }

        bool impossible = 0;

        if (q.empty()) {
            impossible = 1;
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (const auto &edge: contracted.adj[v]) {
                if (dist[edge->v] == -1) {
                    dist[edge->v] = dist[v] + 1;
                    q.push(edge->v);
                }
            }
        }

        // DEBUG
        // for (int c = 0; c < contracted.V; c++) {
        //     printf("%d:", c);
        //     for (int v = 0; v < g.V; v++) {
        //         if (cmp[v] == c) {
        //             printf(" %d", v + 1);
        //         }
        //     }
        //     printf("\n");
        //     printf("has_odd_cycle: %s\n", has_odd_cycle[c] ? "yes" : "no");
        //     printf("dist: %d\n", dist[c]);
        //     printf("\n");
        // }

        auto up = make_vector<int>(LOG, contracted.V, 0);
        auto lo = make_vector<int>(LOG, contracted.V, 0);
        vector<int> depth(contracted.V);

        auto prep_bin_lift = y_combinator([&](auto dfs, int v, int prv, int d = 0) -> void {
            up[0][v] = prv;
            lo[0][v] = dist[v];
            depth[v] = d;

            for (const auto &edge: contracted.adj[v]) {
                if (edge->v == prv) {
                    continue;
                }
                dfs(edge->v, v, d + 1);
            }
        });

        prep_bin_lift(0, 0);

        for (int l = 1; l < LOG; l++) {
            for (int v = 0; v < contracted.V; v++) {
                up[l][v] = up[l - 1][up[l - 1][v]];
                lo[l][v] = min(lo[l - 1][v], lo[l - 1][up[l - 1][v]]);
            }
        }

        lint ans = 0;

        int Q;
        for (cin >> Q; Q--;) {
            int u, v;
            cin >> u >> v;
            u = cmp[u - 1], v = cmp[v - 1];

            if (impossible) {
                ans += -1;
                continue;
            }

            int best = min(dist[u], dist[v]);

            if (depth[u] > depth[v]) {
                swap(u, v);
            }

            for (int l = LOG - 1; l >= 0; l--) {
                if (depth[up[l][v]] >= depth[u]) {
                    best = min(best, lo[l][v]);
                    v = up[l][v];
                }
            }

            if (u == v) {
                ans += best;
                continue;
            }

            assert(depth[u] == depth[v]);

            for (int l = LOG - 1; l >= 0; l--) {
                if (up[l][u] != up[l][v]) {
                    best = min(best, min(lo[l][u], lo[l][v]));
                    u = up[l][u];
                    v = up[l][v];
                }
            }

            best = min(best, min(lo[0][u], lo[0][v]));
            u = up[0][u], v = up[0][v];

            assert(u == v);

            best = min(best, dist[u]);

            ans += best;
        }

        printf("%lld\n", ans);
    }

    return 0;
}
