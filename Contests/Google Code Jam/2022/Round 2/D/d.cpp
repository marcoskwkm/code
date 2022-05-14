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
        int N, C;
        cin >> N >> C;
        if (N > 5000) {
            abort();
        }

        vector<int> vl0, vr0, vl1, vr1;
        for (int i = 0; i < N; i++) {
            int x, k;
            cin >> x >> k;
            if (x < 0) {
                if (k == 0) vl0.push_back(-x);
                else vl1.push_back(-x);
            } else {
                if (k == 0) vr0.push_back(x);
                else vr1.push_back(x);
            }
        }

        sort(vl0.begin(), vl0.end());
        sort(vl1.begin(), vl1.end());
        sort(vr0.begin(), vr0.end());
        sort(vr1.begin(), vr1.end());

        auto solve = [&]() {
            auto dp = make_vector<lint>(vr0.size() + 1, vr1.size() + 1, -1LL);

            auto go = y_combinator([&](auto go, size_t l, size_t r) -> lint {
                if (dp[l][r] != -1) {
                    return dp[l][r];
                }

                if (l == vr0.size() && r == vr1.size()) {
                    return dp[l][r] = 0;
                }

                lint ret = LINF;

                if (l + 2 <= vr0.size()) {
                    lint dist = vr0[l + 1];
                    ret = min(ret, 2 * dist + C + go(l + 2, r));
                }

                if (l + 1 <= vr0.size()) {
                    lint dist = vr0[l];
                    ret = min(ret, 2 * dist + go(l + 1, r));
                }

                if (r + 2 <= vr1.size()) {
                    lint dist = vr1[r + 1];
                    ret = min(ret, 2 * dist + C + go(l, r + 2));
                }

                if (r + 1 <= vr1.size()) {
                    lint dist = vr1[r];
                    ret = min(ret, 2 * dist + go(l, r + 1));
                }

                if (l + 1 <= vr0.size() && r + 1 <= vr1.size()) {
                    lint dist = max(vr0[l], vr1[r]);
                    ret = min(ret, 2 * dist + go(l + 1, r + 1));
                }

                return dp[l][r] = ret;
            });

            return go(0, 0);
        };

        lint ans = solve();
        vr0 = vl0;
        vr1 = vl1;
        ans += solve();

        printf("%lld\n", ans);
    }

    return 0;
}
