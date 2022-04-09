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
const int MAXX = 110;

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

namespace RMQ {
template<class T> struct min {
    T operator()(T a, T b) { return std::min(a, b); }
};

template<class T> struct max {
    T operator()(T a, T b) { return std::max(a, b); }
};

// Static RMQ structure.
// Builds in O(NlogN) and computes queries in O(1).
template<class T, class Agg = min<T>> struct StaticRMQ {
    Agg agg = Agg();
    vector<vector<T>> rmq;
    int N, K;

    StaticRMQ(const vector<T> &v) {
        N = v.size();
        K = 32 - __builtin_clz(N);
        rmq = vector<vector<T>>(K);

        for (int i = 0; i < K; i++)
            rmq[i].resize(N);
        for (int i = 0; i < N; i++)
            rmq[0][i] = v[i];
        for (int k = 1; k < K; k++)
            for (int i = 0; i < N; i++)
                rmq[k][i] = agg(rmq[k - 1][i], rmq[k - 1][std::min(N - 1, i + (1 << (k - 1)))]);
    }

    T get(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return agg(rmq[k][l], rmq[k][r - (1 << k) + 1]);
    }
};
} // namespace RMQ

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int E, W;
        cin >> E >> W;

        vector<vector<int>> weights(W, vector<int>(E));

        for (int e = 0; e < E; e++) {
            for (int w = 0; w < W; w++) {
                cin >> weights[w][e];
            }
        }

        vector<RMQ::StaticRMQ<int>> rmq;
        for (int w = 0; w < W; w++) {
            rmq.push_back(RMQ::StaticRMQ(weights[w]));
        }

        vector<vector<int>> cst(E, vector<int>(E));
        for (int l = 0; l < E; l++) {
            for (int r = l; r < E; r++) {
                for (int w = 0; w < W; w++) {
                    cst[l][r] += 2 * rmq[w].get(l, r);
                }
            }
        }

        vector<vector<int>> dp(E, vector<int>(E, -1));
        auto go = y_combinator([&](auto go, int l, int r) -> int {
            if (dp[l][r] != -1) {
                return dp[l][r];
            }

            if (l == r) {
                return dp[l][r] = 0;
            }

            dp[l][r] = INF;
            for (int i = l; i < r; i++) {
                dp[l][r] = min(dp[l][r],
                               go(l, i) + cst[l][i] + go(i + 1, r) + cst[i + 1][r] - 2 * cst[l][r]);
            }

            return dp[l][r];
        });

        printf("Case #%d: %d\n", t, cst[0][E - 1] + go(0, E - 1));
    }
    return 0;
}
