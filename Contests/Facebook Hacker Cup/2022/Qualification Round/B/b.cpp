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
        int R, C;
        cin >> R >> C;
        vector<string> grid;
        for (int r = 0; r < R; r++) {
            grid.push_back(read<string>());
        }

        auto deg = make_vector<int>(R, C, 0);

        auto is_valid = [&](int r, int c) {
            return r >= 0 && c >= 0 && r < R && c < C && grid[r][c] != '#';
        };

        vector<pii> delta = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                for (auto [dr, dc]: delta) {
                    if (is_valid(r + dr, c + dc)) {
                        deg[r][c]++;
                    }
                }
            }
        }

        queue<pii> q;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] != '#' && deg[r][c] < 2) {
                    q.push({r, c});
                }
            }
        }

        auto forb = make_vector<bool>(R, C, false);
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            forb[r][c] = 1;
            for (auto [dr, dc]: delta) {
                int nr = r + dr, nc = c + dc;
                if (is_valid(nr, nc)) {
                    if (--deg[nr][nc] == 1) {
                        q.push({nr, nc});
                    }
                }
            }
        }

        bool ok = 1;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == '^' && forb[r][c]) {
                    ok = 0;
                }
            }
        }

        printf("Case #%d: %s\n", t, ok ? "Possible" : "Impossible");
        if (ok) {
            for (int r = 0; r < R; r++) {
                for (int c = 0; c < C; c++) {
                    printf("%c", (forb[r][c] || grid[r][c] == '#') ? grid[r][c] : '^');
                }
                printf("\n");
            }
        }
    }

    return 0;
}
