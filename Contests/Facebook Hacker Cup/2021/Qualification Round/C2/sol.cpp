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
        int n, k;
        cin >> n >> k;
        vector<lint> cst(n);
        vector<vector<int>> adj(n);
        readArray(cst, n);

        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }

        auto dfs = y_combinator([&](auto _dfs, int v, int prv) -> vector<lint> {
            vector<lint> dp[2];
            dp[0] = vector<lint>(k + 1, cst[v]);
            dp[1] = vector<lint>(k + 1, -INF);

            for (int nxt: adj[v]) {
                if (nxt == prv)
                    continue;
                vector<lint> nxtdp[2];
                nxtdp[0] = dp[0];
                nxtdp[1] = dp[1];

                // if (v == 0) {
                //     printf("before %d:\n", nxt + 1);
                //     for (int i = 0; i <= k; i++)
                //         printf("%lld ", dp[0][i]);
                //     printf("\n");
                //     for (int i = 0; i <= k; i++)
                //         printf("%lld ", dp[1][i]);
                //     printf("\n");
                // }
                vector<lint> values = _dfs(nxt, v);
                for (int i = k; i >= 0; i--) {
                    for (int take = 0; take <= i; take++) {
                        nxtdp[1][i] = max(nxtdp[1][i], dp[0][i - take] + values[take]);
                    }
                    for (int take = 0; take + 1 <= i; take++) {
                        nxtdp[0][i] = max(nxtdp[0][i], dp[1][i - take - 1] + values[take]);
                    }
                }
                dp[0] = nxtdp[0];
                dp[1] = nxtdp[1];
                // if (v == 0) {
                //     printf("after %d:\n", nxt + 1);
                //     for (int i = 0; i <= k; i++)
                //         printf("%lld ", dp[0][i]);
                //     printf("\n");
                //     for (int i = 0; i <= k; i++)
                //         printf("%lld ", dp[1][i]);
                //     printf("\n");
                // }
            }

            vector<lint> merged(k + 1);
            for (int i = 0; i <= k; i++) {
                merged[i] = max(dp[0][i], dp[1][i]);
            }

            printf("%d:\n", v + 1);
            for (int i = 0; i <= k; i++)
                printf("%lld ", dp[0][i]);
            printf("\n");
            for (int i = 0; i <= k; i++)
                printf("%lld ", dp[1][i]);
            printf("\n");
            for (int i = 0; i <= k; i++)
                printf("%lld ", merged[i]);
            printf("\n");

            if (v == 0) {
                merged[k] = dp[0][k];
                if (k > 0)
                    merged[k] = max(merged[k], dp[1][k - 1]);
            }

            return merged;
        });

        printf("Case #%d: %lld\n", t, dfs(0, -1)[k]);
    }
    return 0;
}
