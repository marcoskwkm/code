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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);

        int N;
        cin >> N;

        vector<vector<int>> adj(N);
        vector<pii> new_edges;

        for (int i = 0; i < N; i++) {
            adj[i].push_back(read() - 1);
            new_edges.push_back({adj[i].back(), i});
        }

        for (int i = 0; i < N; i++) {
            adj[i].push_back(read() - 1);
            new_edges.push_back({adj[i].back(), i});
        }

        bool ok = 1;

        for (int v = 0; v < N; v++) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    int w = adj[adj[v][i]][j];

                    if (w == v) {
                        ok = 0;
                    }

                    new_edges.push_back({v, w});
                    new_edges.push_back({w, v});
                }
            }
        }

        if (!ok) {
            printf("IMPOSSIBLE\n");
            continue;
        }

        for (auto [u, v]: new_edges) {
            adj[u].push_back(v);
        }

        for (int i = 0; i < N; i++) {
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        }

        vector<int> satur(N, 0);
        auto used = make_vector<int>(N, 13, 0);
        vector<int> color(N, -1);
        vector<int> uncolor_deg(N);

        set<tiii, greater<tiii>> s;

        for (int v = 0; v < N; v++) {
            uncolor_deg[v] = adj[v].size();
            s.insert({0, uncolor_deg[v], v});
        }

        while (!s.empty()) {
            int v = get<2>(*s.begin());
            s.erase(s.begin());

            if (color[v] != -1) {
                continue;
            }

            for (int c = 0; c < 13; c++) {
                if (!used[v][c]) {
                    color[v] = c;
                    break;
                }
            }

            assert(color[v] != -1);

            for (int nxt: adj[v]) {
                if (!used[nxt][color[v]]) {
                    used[nxt][color[v]] = 1;
                    satur[nxt]++;
                }
                s.erase({satur[nxt], uncolor_deg[nxt], nxt});
                uncolor_deg[nxt]--;
                s.insert({satur[nxt], uncolor_deg[nxt], nxt});
            }
        }

        string mascots = "ACDEHIJKMORST";

        for (int i = 0; i < N; i++) {
            printf("%c", mascots[color[i]]);
        }
        printf("\n");
    }

    return 0;
}
