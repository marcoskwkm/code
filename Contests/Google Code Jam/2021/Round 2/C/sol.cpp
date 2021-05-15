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
const int MOD = (int)1e9 + 7;

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

    vector<lint> fat(MAXN);
    vector<lint> invfat(MAXN);
    vector<lint> inv(MAXN);
    fat[0] = fat[1] = invfat[0] = invfat[1] = 1;
    inv[1] = 1;
    for (int n = 2; n < MAXN; n++) {
        fat[n] = fat[n - 1] * n % MOD;
        inv[n] = MOD - MOD / n * inv[MOD % n] % MOD;
        invfat[n] = invfat[n - 1] * inv[n] % MOD;
    }

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        cin >> n;
        vector<int> v(n);
        readArray(v, n);
        vector<vector<int>> adj(n);
        vector<int> parent(n, -1);
        bool flag = (v[0] == 1);
        stack<int> st;

        int root = -1;
        for (int i = 0; i < n; i++) {
            if (v[i] == 1) { root = i; }
            if (v[i] > (int)st.size() + 1) {
                flag = 0;
                break;
            }
            int last_removed = -1;
            while (1 + (int)st.size() > v[i]) {
                last_removed = st.top();
                st.pop();
            }
            if (last_removed != -1) parent[last_removed] = i;
            if (!st.empty()) { parent[i] = st.top(); }
            st.push(i);
        }

        if (!flag) {
            printf("Case #%d: 0\n", t);
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) { adj[parent[i]].push_back(i); }
        }

        // debug("root = %d\n", root);
        // for (int i = 0; i < n; i++) {
        //     debug("%d: ", i);
        //     for (size_t j = 0; j < adj[i].size(); j++) { debug(" %d", adj[i][j]); }
        //     debug("\n");
        // }

        vector<lint> dp(n);
        auto go = y_combinator([&](auto go, int node) -> lint {
            int sum = 0;
            lint ret = 1;
            vector<int> cnt;
            for (int nxt: adj[node]) {
                cnt.push_back(go(nxt));
                sum += cnt.back();
                ret = ret * dp[nxt] % MOD;
            }
            ret = ret * fat[sum] % MOD;
            for (int q: cnt) { ret = ret * invfat[q] % MOD; }
            dp[node] = ret;
            // debug("dp[%d] = %lld, sum = %d\n", node, ret, sum);
            return 1 + sum;
        });

        go(root);

        printf("Case #%d: %lld\n", t, dp[root]);
    }
    return 0;
}
