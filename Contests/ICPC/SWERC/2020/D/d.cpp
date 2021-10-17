#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

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

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

// Directed weighted graph
template<class WTYPE> struct WeightedGraph {
    int V;
    vector<vector<pair<int, WTYPE>>> adj;

    WeightedGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, WTYPE w) { adj[u].push_back(make_pair(v, w)); }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, L, U;
    cin >> n >> m >> L >> U;
    WeightedGraph<lint> g(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
        g.add_edge(v, u, w);
    }

    vector<lint> d(n, LINF);
    d[0] = 0;
    set<pll> pq;
    pq.insert(pii(0, 0));

    while (!pq.empty()) {
        int v = pq.begin()->second;
        pq.erase(pq.begin());

        for (const auto &edge: g.adj[v]) {
            if (d[v] + edge.second < d[edge.first]) {
                pq.erase(pll(d[edge.first], edge.first));
                d[edge.first] = d[v] + edge.second;
                pq.insert(pll(d[edge.first], edge.first));
            }
        }
    }

    int ans = 0;
    for (int v = 0; v < n; v++) {
        if (2 * d[v] >= U)
            continue;
        for (const auto &edge: g.adj[v]) {
            if (d[edge.first] > d[v] || (d[edge.first] == d[v] && v < edge.first))
                ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}
