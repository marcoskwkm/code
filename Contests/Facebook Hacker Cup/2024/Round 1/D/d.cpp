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
const int MAXV = 1e9;

template<class T = int>
inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T>
inline vector<T> read_vector(int n) {
    vector<T> v(n);
    read_array(v, n);
    return v;
}

template<class T>
vector<T> make_vector(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template<class T, class... Args>
auto make_vector(size_t head, Args &&...rem) {
    auto inner = make_vector<T>(rem...);
    return vector<decltype(inner)>(head, inner);
}

template<class T, class C = vector<T>>
inline void print_array(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

// Ring of integers modulo n
template<int mod>
struct ZN {
    int x;
    ZN() : x(0) {}
    ZN(int _x) : x((_x % mod + mod) % mod) {}
    ZN operator+(ZN that) { return ZN((x + that.x) % mod); }
    ZN operator-(ZN that) { return ZN((x - that.x + mod) % mod); }
    ZN operator*(ZN that) { return ZN((lint(x) * that.x) % mod); }
    ZN &operator+=(ZN that) { return *this = *this + that; }
    ZN &operator-=(ZN that) { return *this = *this - that; }
    ZN &operator*=(ZN that) { return *this = *this * that; }
    ZN operator-() { return ZN(-x); }
    bool operator==(ZN that) { return x == that.x; }
    bool operator!=(ZN that) { return x != that.x; }
    friend ostream &operator<<(ostream &os, ZN a) { return os << a.x; }
    friend istream &operator>>(istream &is, ZN &a) { return is >> a.x; }
};
using Z = ZN<998244353>;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        string S;
        int K;
        cin >> S >> K;
        int n = S.size();

        vector<Z> dpz(n + 2);
        vector<bool> has_sol(n + 2);

        auto can_join = [](char l, char r) {
            return l == '?' || l == '1' || (l == '2' && (r <= '6' || r == '?'));
        };

        dpz[n + 1] = 1;
        has_sol[n + 1] = 1;
        for (int i = n; i >= 1; i--) {
            char cur = S[i - 1], nxt = (i == n ? 0 : S[i]);
            if (cur != '0') {
                dpz[i] += dpz[i + 1];
                has_sol[i] = has_sol[i] || has_sol[i + 1];
            }
            if (i == n) continue;
            if (can_join(cur, nxt)) {
                dpz[i] += dpz[i + 2];
                has_sol[i] = has_sol[i] || has_sol[i + 2];
            }
        }

        auto get_hi = [&](int prv, int i) {
            char cur = S[i - 1], nxt = (i == n ? 0 : S[i]);
            int hi = (prv == 2 ? 6 : 9);
            if (nxt != 0 && has_sol[i + 2]) {
                hi = 2;
                if (isdigit(nxt) && nxt >= '7') hi = 1;
            }
            return hi;
        };

        auto dp = make_vector<lint>(n + 2, 10, 0ll);

        for (int prv = 0; prv <= 9; prv++) {
            dp[n + 1][prv] = 1;
        }
        for (int i = n; i >= 1; i--) {
            for (int prv = 0; prv <= 9; prv++) {
                char cur = S[i - 1], nxt = (i == n ? 0 : S[i]);
                if (isdigit(cur)) {
                    dp[i][prv] = dp[i + 1][S[i - 1] - '0'];
                    continue;
                }

                int hi = get_hi(prv, i);

                for (int d = 1; d <= hi; d++) {
                    dp[i][prv] += dp[i + 1][d];
                }

                dp[i][prv] = min<lint>(dp[i][prv], MAXV);
            }
        }

        int prv = 0;
        for (int i = 1; i <= n; i++) {
            char &cur = S[i - 1], nxt = (i == n ? 0 : S[i]);
            if (isdigit(cur)) {
                prv = cur - '0';
                continue;
            }

            int hi = get_hi(prv, i);

            for (int d = hi; d >= 1; d--) {
                if (dp[i + 1][d] >= K) {
                    cur = d + '0';
                    prv = d;
                    break;
                } else {
                    K -= dp[i + 1][d];
                }
            }
        }

        printf("Case #%d: %s %d\n", t, S.c_str(), dpz[1].x);
    }

    return 0;
}
