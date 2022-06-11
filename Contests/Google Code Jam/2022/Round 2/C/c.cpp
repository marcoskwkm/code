#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const string IMPOSSIBLE = "IMPOSSIBLE";

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

struct FlowEdge {
    using FType = int;
    static const int MAX_EDGES = (int)1e7;
    static int edge_cnt;
    static array<FlowEdge, MAX_EDGES> edges;

    int v;
    FType cap;
    FlowEdge *rev;

    FlowEdge() {}
    FlowEdge(int _v, FType _cap) : v(_v), cap(_cap), rev(NULL) {}

    static void add(Graph<FlowEdge> &g, int u, int v, FType cap) {
        edges[edge_cnt++] = FlowEdge(v, cap);
        edges[edge_cnt++] = FlowEdge(u, 0);
        auto uv = &edges[edge_cnt - 2];
        auto vu = &edges[edge_cnt - 1];
        uv->rev = vu;
        vu->rev = uv;
        g.adj[u].push_back(uv);
        g.adj[v].push_back(vu);
    }
};

int FlowEdge::edge_cnt = 0;
array<FlowEdge, FlowEdge::MAX_EDGES> FlowEdge::edges;

template<class EType> struct Dinic {
    using FType = typename EType::FType;
    vector<int> ptr, dist;
    Graph<EType> &g;

    Dinic(Graph<EType> &_g) : g(_g) {
        ptr.resize(g.V);
        dist.resize(g.V);
    }

    bool bfs(int s, int t) {
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front();
            if (dist[v] == dist[t])
                break;
            q.pop();
            for (const auto edge: g.adj[v]) {
                if (dist[edge->v] == -1 && edge->cap) {
                    dist[edge->v] = dist[v] + 1;
                    q.push(edge->v);
                }
            }
        }
        return dist[t] != -1;
    }

    FType dfs(int v, int t, FType flow) {
        if (v == t) {
            return flow;
        }
        for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
            auto edge = g.adj[v][p];
            if (dist[edge->v] == dist[v] + 1 && edge->cap) {
                FType got = dfs(edge->v, t, min(flow, edge->cap));
                if (got) {
                    edge->cap -= got;
                    edge->rev->cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    FType max_flow(int s, int t) {
        FType ret = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (FType got = dfs(s, t, numeric_limits<FType>::max()))
                ret += got;
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int _t = 1, T;
    for (cin >> T; _t <= T; _t++) {
        printf("Case #%d: ", _t);
        int N;
        cin >> N;
        vector<pll> children, candies;
        Graph<FlowEdge> g(2 * N + 2);
        FlowEdge::edge_cnt = 0;
        int s = 2 * N, t = 2 * N + 1;

        for (int i = 0; i < N; i++) {
            FlowEdge::add(g, s, i, 1);
            FlowEdge::add(g, N + i, t, 1);
            lint x, y;
            cin >> x >> y;
            children.push_back({x, y});
        }
        for (int i = 0; i < N + 1; i++) {
            lint x, y;
            cin >> x >> y;
            candies.push_back({x, y});
        }

        auto dist = [&](pll a, pll b) {
            auto [ax, ay] = a;
            auto [bx, by] = b;
            return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
        };

        for (int i = 0; i < N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dist(children[i], candies[j]) <= dist(children[i], candies[0])) {
                    FlowEdge::add(g, i, N + j - 1, 1);
                }
            }
        }

        Dinic dinic(g);

        if (dinic.max_flow(s, t) < N) {
            printf("%s\n", IMPOSSIBLE.c_str());
            continue;
        }

        printf("POSSIBLE\n");

        vector<int> match(2 * N);
        vector<bool> done(2 * N);

        for (int i = 0; i < N; i++) {
            for (auto edge: g.adj[i]) {
                if (edge->v == s) {
                    continue;
                }
                if (edge->cap == 0) {
                    match[i] = edge->v;
                    match[edge->v] = i;
                    break;
                }
            }
        }

        vector<vector<int>> ord_candies;
        for (int i = 0; i < N; i++) {
            vector<int> ord;
            for (int j = 1; j <= N; j++) {
                if (dist(children[i], candies[j]) <= dist(children[i], candies[0])) {
                    ord.push_back(j);
                }
            }
            sort(ord.begin(), ord.end(), [&](int ca, int cb) {
                return dist(children[i], candies[ca]) > dist(children[i], candies[cb]);
            });
            ord_candies.push_back(ord);
        }

        vector<pii> sol;

        auto clean = [&]() {
            bool rep = 1;
            while (rep) {
                rep = 0;
                for (int i = 0; i < N; i++) {
                    if (done[i]) {
                        continue;
                    }
                    while (done[ord_candies[i].back() + N - 1]) {
                        ord_candies[i].pop_back();
                    }
                    if (match[i] == ord_candies[i].back() + N - 1) {
                        done[i] = done[match[i]] = 1;
                        sol.push_back({i + 1, match[i] - N + 2});
                        rep = 1;
                    }
                }
            }
        };

        clean();

        while (sol.size() < N) {
            for (int i = 0; i < N; i++) {
                if (done[i]) {
                    continue;
                }

                int cur = i;
                vector<bool> seen(N);
                stack<int> st{{cur}};
                seen[cur] = 1;
                while (1) {
                    int candy = N + ord_candies[cur].back() - 1;
                    int nxt = match[candy];
                    if (seen[nxt]) {
                        while (1) {
                            int u = st.top();
                            st.pop();
                            int v = N + ord_candies[u].back() - 1;
                            match[u] = v;
                            match[v] = u;
                            done[u] = done[v] = 1;
                            sol.push_back({u + 1, v - N + 2});
                            if (u == nxt) {
                                break;
                            }
                        }
                        break;
                    }

                    seen[nxt] = 1;
                    st.push(nxt);
                    cur = nxt;
                }

                clean();
            }
        }

        for (auto [a, b]: sol) {
            printf("%d %d\n", a, b);
        }
    }

    return 0;
}
