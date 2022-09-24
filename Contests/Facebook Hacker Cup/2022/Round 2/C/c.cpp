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
const lint P = (int)1e9 + 7;
const lint MAXS = 3000 * 3000 + 10;

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

    vector<lint> f(MAXS), fi(MAXS), inv(MAXS);
    f[0] = f[1] = fi[0] = fi[1] = inv[1] = 1;

    for (lint n = 2; n < MAXS; n++) {
        f[n] = f[n - 1] * n % P;
        inv[n] = P - P / n * inv[P % n] % P;
        fi[n] = fi[n - 1] * inv[n] % P;
    }

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n, k;
        cin >> n >> k;
        lint a = 0, b = 0, c = 0, d = 0;
        int w = 0;
        cin >> c >> w;
        for (int i = 1; i < n; i++) {
            int q, wi;
            cin >> q >> wi;
            if (wi < w) {
                a += q;
            } else if (wi == w) {
                b += q;
            } else {
                d += q;
            }
        }

        lint p0d = 0;
        if (a + b + c > k) {
            p0d = f[a + b + c] * fi[a + b + c - k - 1] % P;
            p0d = p0d * fi[a + b + c + d] % P;
            p0d = p0d * f[a + b + c + d - k - 1] % P;
        }

        lint paa = 0;
        if (a > k) {
            paa = f[a] * fi[a - k - 1] % P;
            paa = paa * fi[a + b + c] % P;
            paa = paa * f[a + b + c - k - 1] % P;
        }

        lint pfc = c * inv[b + c] % P;

        lint ans = p0d * (1 - paa) % P;
        ans = ans * pfc % P;
        ans = (ans + P) % P;

        printf("Case #%d: %lld\n", t, ans);
    }

    return 0;
}
