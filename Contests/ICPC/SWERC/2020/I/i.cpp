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
const int MAXN = (int)1e5 + 10;

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

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;

    Graph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v) { adj[u].push_back(v); }
};

int dist[MAXN];

void bfs(int s, Graph &g) {
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;

    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int nxt: g.adj[v]) {
            if (dist[nxt] == -1) {
                dist[nxt] = dist[v] + 1;
                q.push(nxt);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(42);

    int n, m;
    cin >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u - 1, v - 1);
        g.add_edge(v - 1, u - 1);
    }

    bfs(0, g);
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) {
            printf("-1\n");
            return 0;
        }
    }

    int ans = 0;
    for (int step = 0; step < 100; step++) {
        int v = rand() % n;
        bfs(v, g);
        int maxd = 0;
        for (int i = 0; i < n; i++)
            maxd = max(maxd, dist[i]);

        int e = 31 - __builtin_clz(maxd);
        while ((1 << e) < maxd)
            e++;
        ans = max(ans, e);
    }

    cout << ans + 1 << endl;

    return 0;
}
