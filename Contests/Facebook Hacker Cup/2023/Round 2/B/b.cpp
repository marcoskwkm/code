#ifdef CLANG
#include "stdcpp.h"
#else
#include <bits/stdc++.h>
#endif
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

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T> inline vector<T> read_vector(int n) {
    vector<T> v(n);
    read_array(v, n);
    return v;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int t = 1, T = read(); t <= T; t++) {
        printf("Case #%d: ", t);
        int N;
        cin >> N;
        auto v = read_vector<int>(2 * N);
        vector<int> s(2 * N);
        for (int i = 0; i < 2 * N; i++) {
            int j = (i + N) % (2 * N);
            s[i] = (v[i] < v[j]) ? -1 : (v[i] > v[j]) ? 1 : 0;
        }

        int last = s.back();
        int ref = -1;
        for (int i = 0; i < 2 * N; i++) {
            if (last >= 0 && s[i] == -1) {
                ref = i;
                break;
            }
            last = s[i];
        }

        if (ref == -1) {
            printf("-1\n");
            continue;
        }

        ref = (ref + N / 2) % (2 * N);

        // printf("ref = %d\n", ref);

        bool ok = 1;

        for (int i = 0; i < N; i++) {
            int idx = (ref + i) % (2 * N);
            if (2 * i < N - 1) {
                if (s[idx] != -1) {
                    // printf("x\n");
                    ok = 0;
                    break;
                }
            } else if (2 * i > N - 1) {
                if (s[idx] != 1) {
                    // printf("y\n");
                    ok = 0;
                    break;
                }
            }

            int opp = (ref + 2 * N - 1 - i) % (2 * N);

            if (v[idx] != v[opp]) {
                // printf("z %d\n", i);
                ok = 0;
                break;
            }
        }

        printf("%d\n", ok ? ref : -1);
    }

    return 0;
}
