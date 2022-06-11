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
            if (dist[v] == dist[t])
                break;
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
        if (v == t)
            return flow;
        for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
            int i = g.adj[v][p];
            int nxt = g.edges[i].v;
            if (dist[nxt] == dist[v] + 1 && g.edges[i].cap) {
                FTYPE got = dfs(nxt, t, min(flow, g.edges[i].cap));
                if (got) {
                    g.edges[i].cap -= got;
                    g.edges[i ^ 1].cap += got;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int _t = 1, T;
    for (cin >> T; _t <= T; _t++) {
        printf("Case #%d: ", _t);
        int N;
        cin >> N;
        vector<pll> children, candies;
        FlowGraph<int> g(2 * N + 2);
        int s = 2 * N, t = 2 * N + 1;

        for (int i = 0; i < N; i++) {
            g.add_edge(s, i, 1);
            g.add_edge(N + i, t, 1);
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
            return (a.first - b.first) * (a.first - b.first) +
                (a.second - b.second) * (a.second - b.second);
        };

        for (int i = 0; i < N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dist(children[i], candies[j]) <= dist(children[i], candies[0])) {
                    g.add_edge(i, N + j - 1, 1);
                }
            }
        }

        Dinic dinic(g);
        int mf = dinic.max_flow(s, t);

        auto val = [&](pii p) {
            return dist(children[p.first], candies[p.second]);
        };

        if (mf < N) {
            printf("%s\n", IMPOSSIBLE.c_str());
        } else {
            printf("POSSIBLE\n");
            vector<pii> pairings;
            for (int i = 0; i < N; i++) {
                for (int edge: g.adj[i]) {
                    if (g.edges[edge].v != s && g.edges[edge].cap == 0) {
                        pairings.push_back({i, g.edges[edge].v - N + 1});
                    }
                }
            }

            for (int k = 0; k < N; k++) {
                for (int i = 0; i < N; i++) {
                    for (int j = i + 1; j < N; j++) {
                        pii si = pairings[i], sj = pairings[j];
                        swap(si.second, sj.second);
                        if (val(pairings[i]) > val(si) && val(pairings[j]) > val(sj)) {
                            swap(pairings[i].second, pairings[j].second);
                        }
                    }
                }
            }

            vector<int> take(N);
            for (auto p: pairings) {
                take[p.first] = p.second;
            }

            vector<bool> done_child(N, 0), done_candy(N + 1, 0);
            queue<int> q;

            auto is_closest = [&](int i, int j) {
                for (int k = 1; k <= N; k++) {
                    if (done_candy[k]) {
                        continue;
                    }
                    if (dist(children[i], candies[k]) < dist(children[i], candies[j])) {
                        return 0;
                    }
                }
                return 1;
            };

            for (int i = 0; i < N; i++) {
                if (is_closest(i, take[i])) {
                    q.push(i);
                    done_child[i] = 1;
                    done_candy[take[i]] = 1;
                }
            }

            int cnt = 0;
            while (!q.empty()) {
                cnt++;
                int child = q.front(), candy = take[q.front()];
                printf("%d %d\n", child + 1, candy + 1);
                q.pop();
                for (int i = 0; i < N; i++) {
                    if (done_child[i]) {
                        continue;
                    }
                    if (is_closest(i, take[i])) {
                        q.push(i);
                        done_child[i] = done_candy[take[i]] = 1;
                    }
                }
            }

            assert(cnt == N);
        }
    }

    return 0;
}
