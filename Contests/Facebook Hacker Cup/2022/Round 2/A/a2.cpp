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
const lint M0 = (int)1e9 + 7;
const lint M1 = (int)1e9 + 9;
const lint P0 = 31, P1 = 131;

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

    vector<lint> pow0(MAXN), pow1(MAXN);
    pow0[0] = pow1[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow0[i] = pow0[i - 1] * P0 % M0;
        pow1[i] = pow1[i - 1] * P1 % M1;
    }

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        cin >> n;

        vector<vector<lint>> bit(2, vector<lint>(n + 1));
        vector<lint> xor_bit(n + 1);
        vector<lint> v(n + 1);
        map<lint, set<int>> pos;

        auto update_xor = [&](int i, int x) {
            for (; i <= n; i += i & -i) {
                xor_bit[i] ^= x;
            }
        };

        auto _get_xor = [&](int i) {
            lint ret = 0;
            for (; i > 0; i -= i & -i) {
                ret ^= xor_bit[i];
            }
            return ret;
        };

        auto get_xor = [&](int l, int r) { return _get_xor(r) ^ _get_xor(l - 1); };

        auto update = [&](int i, int x) {
            for (; i <= n; i += i & -i) {
                if (x > 0) {
                    bit[0][i] += pow0[x];
                    bit[1][i] += pow1[x];
                } else {
                    bit[0][i] += M0 - pow0[-x];
                    bit[1][i] += M1 - pow1[-x];
                }
                bit[0][i] %= M0;
                bit[1][i] %= M1;
            }
        };

        auto _get = [&](int c, int i) {
            lint ret = 0;
            for (; i > 0; i -= i & -i) {
                ret += bit[c][i];
            }
            return ret % (c == 0 ? M0 : M1);
        };

        auto get = [&](char c, int l, int r) {
            lint ret = _get(c, r) - _get(c, l - 1);
            if (c == 0) {
                return (ret + M0) % M0;
            } else {
                return (ret + M1) % M1;
            }
        };

        auto has = [&](lint x, int l, int r) {
            auto it = pos.find(x);
            if (it == pos.end()) {
                return false;
            }

            auto it2 = it->second.lower_bound(l);

            return it2 != it->second.end() && *it2 <= r;
        };

        auto solve = [&](int l, int r) {
            lint odd = get_xor(l, r);

            if (odd < 1 || odd >= MAXN) {
                return 0;
            }

            int m = (l + r) / 2;
            bool has_left = has(odd, l, m);
            bool has_right = has(odd, m, r);

            if (has_left) {
                lint hash_left_0 = (get(0, l, m) - pow0[odd] + M0) % M0;
                lint hash_left_1 = (get(1, l, m) - pow1[odd] + M1) % M1;
                lint hash_right_0 = get(0, m + 1, r);
                lint hash_right_1 = get(1, m + 1, r);

                if (hash_left_0 == hash_right_0 && hash_left_1 == hash_right_1) {
                    return 1;
                }
            }

            if (has_right) {
                lint hash_left_0 = get(0, l, m - 1);
                lint hash_left_1 = get(1, l, m - 1);
                lint hash_right_0 = (get(0, m, r) - pow0[odd] + M0) % M0;
                lint hash_right_1 = (get(1, m, r) - pow1[odd] + M1) % M1;

                if (hash_left_0 == hash_right_0 && hash_left_1 == hash_right_1) {
                    return 1;
                }
            }

            return 0;
        };

        for (int i = 1; i <= n; i++) {
            cin >> v[i];
            update(i, v[i]);
            update_xor(i, v[i]);
            pos[v[i]].insert(i);
        }

        int q;
        int ans = 0;
        for (cin >> q; q--;) {
            int k, l, r;
            cin >> k >> l >> r;
            if (k == 1) {
                update(l, -v[l]);
                update_xor(l, v[l]);
                pos[v[l]].erase(l);

                v[l] = r;

                update(l, v[l]);
                update_xor(l, v[l]);
                pos[v[l]].insert(l);
            } else {
                ans += solve(l, r);
            }
        }

        printf("Case #%d: %d\n", t, ans);
    }

    return 0;
}
