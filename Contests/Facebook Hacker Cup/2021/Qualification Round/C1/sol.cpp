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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        cin >> n;
        vector<lint> cst(n);
        vector<vector<int>> adj(n);
        readArray(cst, n);

        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }

        auto dfs = y_combinator([&](auto _dfs, int v, int prv) -> lint {
            vector<lint> values;
            for (int nxt: adj[v]) {
                if (nxt == prv)
                    continue;
                values.push_back(_dfs(nxt, v));
            }

            sort(values.begin(), values.end(), greater<lint>());

            if (v == 0) {
                if (values.size() == 0)
                    return cst[v];
                else if (values.size() == 1)
                    return values[0] + cst[v];
                else
                    return values[0] + values[1] + cst[v];
            } else {
                if (values.size() == 0)
                    return cst[v];
                else
                    return values[0] + cst[v];
            }
        });

        printf("Case #%d: %lld\n", t, dfs(0, -1));
    }
    return 0;
}
