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
        printf("Case #%d:", t);
        int N, K;
        cin >> N >> K;
        vector<lint> v(N);
        read_array(v, N);
        lint s1 = 0;
        lint s2 = 0;
        for (int i = 0; i < N; i++) {
            s1 += v[i];
            for (int j = i + 1; j < N; j++) {
                s2 += v[i] * v[j];
            }
        }

        if (K == 1) {
            if (s1 == 0) {
                if (s2 == 0) {
                    printf(" 0\n");
                } else {
                    printf(" IMPOSSIBLE\n");
                }
            } else if (s2 % s1 != 0) {
                printf(" IMPOSSIBLE\n");
            } else {
                printf(" %lld\n", -s2 / s1);
            }
        } else {
            lint x1 = 1 - s1;
            s2 += s1 * x1;
            lint x2 = -s2;
            printf(" %lld %lld\n", x1, x2);
        }
    }

    return 0;
}
