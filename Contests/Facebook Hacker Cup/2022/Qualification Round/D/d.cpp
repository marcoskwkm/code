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
const int N_THREADS = 100;

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
        debug("Case %d/%d...\n", t, T);

        int n, m, q;
        cin >> n >> m >> q;
        map<pii, int> edges;
        vector<vector<pii>> adj(n);
        vector<bitset<200000>> has_edge(n);

        for (int i = 0; i < m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            u--, v--;
            if (u > v) {
                swap(u, v);
            }
            edges[{u, v}] = c;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
            has_edge[u].set(v);
            has_edge[v].set(u);
        }

        vector<pii> query(q);
        vector<lint> answer(q);

        auto get = [&](int u, int v) {
            auto it = edges.find(u < v ? pii(u, v) : pii(v, u));
            if (it == edges.end()) {
                return 0;
            }
            return it->second;
        };

        auto solve = [&](int start_i) {
            for (int i = start_i; i < q; i += N_THREADS) {
                auto [u, v] = query[i];

                if (u < 0) {
                    continue;
                }

                if (adj[u].size() > adj[v].size()) {
                    swap(u, v);
                }
                lint ans = 2 * get(u, v);
                for (auto [w, c]: adj[u]) {
                    if (has_edge[v][w]) {
                        ans += min(c, get(v, w));
                    }
                }
                answer[i] = ans;
            }
        };

        map<pii, int> seen;

        for (int i = 0; i < q; i++) {
            int x = read() - 1, y = read() - 1;
            if (x > y) {
                swap(x, y);
            }
            auto it = seen.find({x, y});
            if (it != seen.end()) {
                query[i] = {-1, it->second};
            } else {
                query[i] = {x, y};
                seen[{x, y}] = i;
            }
        }

        vector<thread> threads;
        for (int i = 0; i < N_THREADS; i++) {
            threads.emplace_back(solve, i);
        }
        for (int i = 0; i < N_THREADS; i++) {
            threads[i].join();
        }

        printf("Case #%d:", t);
        for (int i = 0; i < q; i++) {
            int actual_i = query[i].first < 0 ? query[i].second : i;
            printf(" %lld", answer[actual_i]);
        }
        printf("\n");
    }

    return 0;
}
