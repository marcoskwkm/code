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
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

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
        int R, C;
        cin >> R >> C;
        auto grid = read_vector<string>(R);

        auto cnt = make_vector<int>(R, C, 0);

        auto go = y_combinator([&](auto f, int r, int c, pii &p) -> int {
            int ret = 1;
            cnt[r][c] = -1;
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr < 0 || nc < 0 || nr >= R || nc >= C) {
                    continue;
                }

                if (grid[nr][nc] == '.') {
                    if (p.first == -1) {
                        p = pii(nr, nc);
                    } else if (p != pii(nr, nc)) {
                        p = pii(-2, -2);
                    }
                } else if (grid[nr][nc] == 'W' && cnt[nr][nc] == 0) {
                    ret += f(nr, nc, p);
                }
            }

            return ret;
        });

        int ans = 0;

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] != 'W' || cnt[r][c] != 0) {
                    continue;
                }

                pii sq(-1, -1);
                int q = go(r, c, sq);

                if (sq.first >= 0 ) {
                    cnt[sq.first][sq.second] += q;
                    ans = max(ans, cnt[sq.first][sq.second]);
                }
            }
        }

        printf("Case #%d: %s\n", t, ans > 0 ? "YES" : "NO");
    }

    return 0;
}
