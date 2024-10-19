// WA

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        const int N = 6, M = 7;
        auto dp = make_vector<short>(7, 7, 7, 7, 7, 7, 7, (short)-1);
        vector<string> grid;
        for (int r = 0; r < N; r++) {
            string s;
            cin >> s;
            grid.push_back(s);
        }
        reverse(grid.begin(), grid.end());

        auto check = [&](vector<int> cols) {
            int ret = 0;
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < M; c++) {
                    bool win = 1;
                    if (r >= cols[c]) continue;
                    for (int i = 1; i < 4; i++) {
                        if (c + i >= M || r >= cols[c + i] || grid[r][c] != grid[r][c + i]) {
                            win = 0;
                            break;
                        }
                    }
                    if (win) ret |= (1 << (grid[r][c] == 'C' ? 0 : 1));
                }
            }
            for (int c = 0; c < M; c++) {
                for (int r = 0; r < N; r++) {
                    bool win = 1;
                    if (r >= cols[c]) continue;
                    for (int i = 1; i < 4; i++) {
                        if (r + i >= N || r + i >= cols[c] || grid[r][c] != grid[r + i][c]) {
                            win = 0;
                            break;
                        }
                    }
                    if (win) ret |= (1 << (grid[r][c] == 'C' ? 0 : 1));
                }
            }
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < M; c++) {
                    bool win = 1;
                    if (r >= cols[c]) continue;
                    for (int i = 1; i < 4; i++) {
                        if (c + i >= M || r + i >= N || r + i >= cols[c + i] ||
                            grid[r][c] != grid[r + i][c + i]) {
                            win = 0;
                            break;
                        }
                    }
                    if (win) ret |= (1 << (grid[r][c] == 'C' ? 0 : 1));
                    win = 1;
                    for (int i = 1; i < 4; i++) {
                        if (c - i < 0 || r + i >= N || r + i >= cols[c - i] ||
                            grid[r][c] != grid[r + i][c - i]) {
                            win = 0;
                            break;
                        }
                    }
                    if (win) ret |= (1 << (grid[r][c] == 'C' ? 0 : 1));
                }
            }

            return ret;
        };

        auto go = [&](this const auto &f, vector<int> &cols, char player) {
            auto &state = dp[cols[0]][cols[1]][cols[2]][cols[3]][cols[4]][cols[5]][cols[6]];
            if (state != -1) return state;

            int res = check(cols);
            if (res) {
                if (false && accumulate(cols.begin(), cols.end(), 0) >= 0) {
                    for (int x: cols)
                        printf("%d", x);
                    printf(" %c %d\n", player, res);
                }
                return state = res;
            }

            for (int col = 0; col < M; col++) {
                if (cols[col] == N) continue;
                if (grid[cols[col]][col] != player) continue;
                cols[col]++;
                res |= f(cols, ('F' + 'C' - player));
                cols[col]--;
            }

            if (false && accumulate(cols.begin(), cols.end(), 0) >= 0) {
                for (int x: cols)
                    printf("%d", x);
                printf(" %c %d\n", player, res);
            }

            return state = res;
        };

        vector<int> state(7, 0);
        int sol = go(state, 'C');
        printf("Case #%d: %c\n", t, sol == 0 ? '0' : sol == 1 ? 'C' : sol == 2 ? 'F' : '?');
    }

    return 0;
}
