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
const int MAXN = (int)1e6 + 10;

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
        vector<vector<int>> bit(30, vector<int>(MAXN));

        auto update = [&](int c, int i, int x) {
            for (; i < MAXN; i += i & -i) {
                bit[c][i] += x;
            }
        };

        auto _get = [&](int c, int i) {
            int ret = 0;
            for (; i > 0; i -= i & -i) {
                ret += bit[c][i];
            }
            return ret;
        };

        auto get = [&](char c, int l, int r) { return _get(c, r) - _get(c, l - 1); };

        auto solve = [&](int l, int r) {
            int odd = -1;
            for (int i = 0; i < 30; i++) {
                if (get(i, l, r) & 1) {
                    if (odd >= 0) {
                        return 0;
                    }
                    odd = i;
                }
            }

            if (odd == -1) {
                return 0;
            }

            int m = (l + r) / 2;
            bool has_left = get(odd, l, m) > 0;
            bool has_right = get(odd, m, r) > 0;

            if (has_left) {
                bool ok = get(odd, l, m) - 1 == get(odd, m + 1, r);

                for (int i = 0; i < 30; i++) {
                    if (i == odd) {
                        continue;
                    }
                    ok = ok && get(i, l, m) == get(i, m + 1, r);
                }

                if (ok) {
                    return 1;
                }
            }

            if (has_right) {
                bool ok = get(odd, l, m - 1) == get(odd, m, r) - 1;

                for (int i = 0; i < 30; i++) {
                    if (i == odd) {
                        continue;
                    }
                    ok = ok && get(i, l, m - 1) == get(i, m, r);
                }

                if (ok) {
                    return 1;
                }
            }

            return 0;
        };

        string s;
        cin >> s;
        for (size_t i = 0; i < s.size(); i++) {
            update(s[i] - 'a', i + 1, 1);
        }

        int q;
        int ans = 0;
        for (cin >> q; q--;) {
            int l, r;
            cin >> l >> r;
            ans += solve(l, r);
        }

        printf("Case #%d: %d\n", t, ans);
    }

    return 0;
}
