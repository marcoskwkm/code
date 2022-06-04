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
    cout << endl;
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    if (x == -1) {
        exit(0);
    }
    return x;
}

int main() {
    int t = 1, T;
    int N, K;
    cin >> T >> N >> K;
    for (; t <= T; t++) {
        vector<int> v(N);

        while (1) {
            read_array(v, N);
            vector<int> colors(N, 0);

            int cur_color = 1;
            for (int i = 0; i < N; i++) {
                if (colors[i] != 0) {
                    continue;
                }

                if (v[i] == i + 1) {
                    colors[i] = cur_color++;
                    continue;
                }

                int cur = i;

                for (int step = 0; step < 8; step++) {
                    colors[cur] = cur_color;
                    cur = v[cur] - 1;
                    if (cur == i) {
                        break;
                    }
                }

                cur_color++;
            }

            print_array<int>(colors);
            fflush(stdout);

            if (read() == 1) {
                break;
            }
        }
    }

    return 0;
}
