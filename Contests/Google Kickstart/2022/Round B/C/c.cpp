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
        int n, d;
        cin >> n >> d;
        vector<int> v(n);
        read_array(v, n);

        lint ans = LINF;

        auto dp = make_vector<lint>(n, n, 2, (lint)-1);

        auto add = [&](lint a, lint b) {
            if (a > b) {
                swap(a, b);
            }
            return min(b - a, a + d - b);
        };

        auto go = y_combinator([&](auto go, int l, int r, int k) -> lint {
            if (dp[l][r][k] != -1) {
                return dp[l][r][k];
            }

            lint extr = k == 0 ? v[l] : v[r];

            if (l == 0 && r == n - 1) {
                return dp[l][r][k] = add(extr, 0);
            }
            lint ret = LINF;
            if (l > 0) {
                ret = min(ret, go(l - 1, r, 0) + add(extr, v[l - 1]));
            }
            if (r + 1 < n) {
                ret = min(ret, go(l, r + 1, 1) + add(extr, v[r + 1]));
            }
            return dp[l][r][k] = ret;
        });

        for (int i = 0; i < n; i++) {
            ans = min(ans, go(i, i, 0));
        }

        printf("Case #%d: %lld\n", t, ans);
    }
    return 0;
}
