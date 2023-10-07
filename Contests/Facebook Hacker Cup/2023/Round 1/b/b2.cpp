#include <numeric>
#ifdef CLANG
#include "stdcpp.h"
#endif
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
        lint P;
        cin >> P;

        printf("Case #%d: ", t);

        vector<int> ans;
        vector<int> sol(100, 0);
        int best = INF;

        auto go = y_combinator([&](auto f, lint n, lint last, lint s, int i) -> void {
            if (n == 1 && s == 41) {
                int got = i + (41 - s);
                if (got < best) {
                    best = got;
                    ans = sol;
                    ans.resize(i);
                }
            }

            for (int d = last; d <= 41; d++) {
                if (n % d == 0 && s + d <= 41) {
                    sol[i] = d;
                    f(n / d, d, s + d, i + 1);
                }
            }
        });

        go(P, 1, 0, 0);

        if (best == INF) {
            printf("-1\n");
            continue;
        }

        printf(" %d", (int)ans.size());

        for (int x: ans) {
            printf(" %d", x);
        }

        printf("\n");
    }

    return 0;
}
