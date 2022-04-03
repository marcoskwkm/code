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

int depth[MAXN], nxt[LOG][MAXN], hi[LOG][MAXN];

bool by_best(int u, int v) {
    bool swapped = 0;
    int maxu = 0, maxv = 0;

    if (depth[u] < depth[v]) {
        swap(u, v);
        swapped = 1;
    }

    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[nxt[i][u]] >= depth[v]) {
            maxu = max(maxu, hi[i][u]);
            u = nxt[i][u];
        }
    }

    for (int i = LOG - 1; i >= 0; i--) {
        if (nxt[i][u] != nxt[i][v]) {
            maxu = max(maxu, hi[i][u]);
            maxv = max(maxv, hi[i][v]);
            u = nxt[i][u];
            v = nxt[i][v];
        }
    }

    maxu = max(maxu, hi[0][u]);
    maxv = max(maxv, hi[0][v]);

    return swapped ? maxv < maxu : maxu < maxv;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int N;
        cin >> N;

        vector<int> fun(N + 1), indeg(N + 1, 0), order;
        readArrayFrom(&fun[1], N);
        readArrayFrom(&nxt[0][1], N);

        memset(depth, -1, sizeof(depth));
        depth[0] = 0;

        auto compute_depth = y_combinator([&](auto compute_depth, int v) -> int {
            if (depth[v] != -1) {
                return depth[v];
            }

            return depth[v] = 1 + compute_depth(nxt[0][v]);
        });

        for (int v = 1; v <= N; v++) {
            indeg[nxt[0][v]]++;
            compute_depth(v);
            hi[0][v] = fun[v];
        }

        for (int v = 1; v <= N; v++) {
            if (indeg[v] == 0) {
                order.push_back(v);
            }
        }

        for (int i = 1; i < LOG; i++) {
            for (int v = 1; v <= N; v++) {
                nxt[i][v] = nxt[i - 1][nxt[i - 1][v]];
                hi[i][v] = max(hi[i - 1][v], hi[i - 1][nxt[i - 1][v]]);
            }
        }

        sort(order.begin(), order.end(), by_best);

        vector<bool> activated(N + 1);
        lint ans = 0;

        auto activate = y_combinator([&](auto activate, int v) -> int {
            if (activated[v]) {
                return 0;
            }

            activated[v] = 1;
            return max(fun[v], activate(nxt[0][v]));
        });

        for (int v: order) {
            int got = activate(v);
            if (t == 4)
                debug("v = %d: %d\n", v, got);
            ans += got;
        }

        printf("Case #%d: %lld\n", t, ans);
    }
    return 0;
}
