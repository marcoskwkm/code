#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })
#define readArrayFrom(it, n) for_each(it, it + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int N;
        cin >> N;

        vector<int> fun(N + 1), order(N), prv(N + 1), depth(N + 1, -1);
        vector<int> rep(N + 1), size(N + 1);
        vector<int> tag(N + 1), weight(N + 1);
        vector<vector<int>> nxt(N + 1);
        readArrayFrom(&fun[1], N);
        readArrayFrom(&prv[1], N);

        auto find = y_combinator(
            [&](auto find, int v) -> int { return rep[v] == v ? v : rep[v] = find(rep[v]); });

        auto join = [&](int u, int v) {
            int ru = find(u), rv = find(v);
            if (ru == rv) {
                return;
            }

            if (size[ru] <= size[rv]) {
                rep[ru] = rv;
                size[rv] += size[ru];
            } else {
                rep[rv] = ru;
                size[ru] += size[rv];
            }
        };

        auto compute_depth = y_combinator([&](auto compute_depth, int v) -> int {
            if (depth[v] != -1) {
                return depth[v];
            }

            return depth[v] = 1 + compute_depth(prv[v]);
        });

        rep[0] = 0;
        size[0] = 1;
        depth[0] = 0;
        fun[0] = INF;
        for (int v = 1; v <= N; v++) {
            compute_depth(v);
            rep[v] = v;
            size[v] = 1;
            order[v - 1] = v;
            nxt[prv[v]].push_back(v);
        }

        sort(order.begin(), order.end(), [&](int u, int v) {
            return fun[u] == fun[v] ? depth[u] < depth[v] : fun[u] < fun[v];
        });

        for (int v: order) {
            int rep = find(prv[v]);
            tag[v] = size[rep];
            join(v, rep);
        }

        vector<vector<int>> jmp(LOG, vector<int>(N + 1));
        auto get_weights = y_combinator([&](auto get_weights, int v) -> void {
            int first_jmp = prv[v];

            if (v > 0 && fun[first_jmp] <= fun[v]) {
                for (int i = LOG - 1; i >= 0; i--) {
                    if (fun[jmp[i][first_jmp]] <= fun[v]) {
                        first_jmp = jmp[i][first_jmp];
                    }
                }
                first_jmp = jmp[0][first_jmp];
            }

            jmp[0][v] = first_jmp;
            for (int i = 1; i < LOG; i++) {
                jmp[i][v] = jmp[i - 1][jmp[i - 1][v]];
            }

            weight[v] = weight[first_jmp] + tag[v];

            for (int to: nxt[v]) {
                get_weights(to);
            }
        });

        get_weights(0);

        sort(order.begin(), order.end(), [&](int u, int v) { return weight[u] < weight[v]; });

        vector<bool> activated(N + 1);
        activated[0] = 1;
        lint ans = 0;

        auto activate = y_combinator([&](auto activate, int v) -> int {
            if (activated[v]) {
                return 0;
            }

            activated[v] = 1;
            return max(fun[v], activate(prv[v]));
        });

        for (int v: order) {
            if (nxt[v].size() == 0) {
                int got = activate(v);
                ans += got;
            }
        }

        printf("Case #%d: %lld\n", t, ans);
    }
    return 0;
}
