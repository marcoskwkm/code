#include <bits/stdc++.h>
using namespace std;

#define debug(args...)                                                                             \
    if (t == 2)                                                                                    \
    fprintf(stderr, args)
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
        auto seen = make_vector<bool>(R, C, false);
        for (int r = 0; r < R; r++) {
            string s;
            cin >> s;
            grid.push_back(s);
        }

        vector<char> ans;
        vector<pii> delta = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
        vector<int> nxt_k = {3, 0, 1, 2};
        vector<char> chr = {'W', 'S', 'E', 'N'};

        auto dfs = y_combinator([&](auto dfs, int r, int c, int s) -> void {
            seen[r][c] = 1;

            for (int i = 0; i < 3; i++) {
                int dir = (s + i + 3) % 4;
                auto [dr, dc] = delta[dir];
                int nr = r + dr, nc = c + dc;

                if (nr < 0 || nc < 0 || nr >= R || nc >= C || seen[nr][nc] || grid[nr][nc] == '#') {
                    ans.push_back(chr[(dir + 1) % 4]);
                } else {
                    ans.push_back(chr[dir]);
                    dfs(nr, nc, dir);
                }
            }

            ans.push_back(chr[(s + 2) % 4]);
        });

        dfs(0, 0, 1);
        ans.back() = 'W';

        bool ok = 1;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == '*' && !seen[r][c]) {
                    ok = 0;
                }
            }
        }

        if (!ok) {
            printf("Case #%d: IMPOSSIBLE\n", t);
        } else {
            printf("Case #%d: ", t);
            for (char c: ans) {
                printf("%c", c);
            }
            printf("\n");
        }
    }
    return 0;
}
