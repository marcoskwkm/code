#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef __int128 lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const lint MOD = (int)1e9 + 7;
const int N_THREADS = 50;

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

    int T = read();
    vector<tuple<int, int, vector<pll>, vector<pll>>> cases;

    for (int i = 0; i < T; i++) {
        int N = read();
        vector<pll> A, B;
        for (int j = 0; j < N; j++) {
            lint x = read(), y = read();
            A.emplace_back(x, y);
        }
        int Q = read();
        for (int j = 0; j < Q; j++) {
            lint x = read(), y = read();
            B.emplace_back(x, y);
        }
        cases.emplace_back(N, Q, A, B);
    }

    vector<lint> ans(T);

    auto solve = [&](int start_idx) {
        for (int i = start_idx; i < T; i++) {
            auto [N, Q, A, B] = cases[i];
            lint sx2 = 0, sy2 = 0, sx = 0, sy = 0;
            for (const auto &[x, y]: A) {
                sx2 = (sx2 + x * x) % MOD;
                sy2 = (sy2 + y * y) % MOD;
                sx = (sx + x) % MOD;
                sy = (sy + y) % MOD;
            }

            lint total_inc = 0;

            for (const auto &[x, y]: B) {
                lint inc_x = sx2 + N * x * x - 2 * x * sx;
                lint inc_y = sy2 + N * y * y - 2 * y * sy;
                total_inc += inc_x + inc_y;
                total_inc %= MOD;
            }

            ans[i] = (total_inc % MOD + MOD) % MOD;
        }
    };

    vector<thread> threads;
    for (int i = 0; i < N_THREADS; i++) {
        threads.emplace_back(solve, i);
    }
    for (int i = 0; i < N_THREADS; i++) {
        threads[i].join();
    }

    for (int t = 0; t < T; t++) {
        printf("Case #%d: %lld\n", t + 1, (long long)ans[t]);
    }

    return 0;
}
