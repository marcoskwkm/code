#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef pair<pii, pii> ppi;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 50;

int grid[2][MAXD][MAXD];

ppi test_horizontal(int n, int m, int i) {
    ppi ret({INF, INF}, {INF, INF});
    for (int f = 0; f + 1 < n; f++) {
        bool ok = 1;
        for (int r = 0; r < n && ok; r++) {
            int nr = -1;
            if (r <= f) nr = f + 1 + f - r;
            else nr = f - (r - (f + 1));
            for (int c = 0; c < m; c++) {
                if (nr < 0 || nr >= n) {
                    if (grid[i][r][c] != 1) {
                        ok = 0;
                        break;
                    }
                }
                else if (!(grid[i][r][c] ^ grid[i][nr][c])) {
                    ok = 0;
                    break;
                }
            }
        }
        if (ok) {
            ppi got(pii(f, 0), pii(f, m - 1));
            if (i == 1) {
                swap(got.first.first, got.first.second);
                swap(got.second.first, got.second.second);
            }
            ret = min(ret, got);
        }
    }
    return ret;
}

ppi test_diagonal(int n, int m, int i) {
    ppi ret({INF, INF}, {INF, INF});
    for (int s = 0; s < n + m - 1; s++) {
        // printf("s = %d\n", s);
        bool ok = 1;        
        int sr = min(n - 1, s);
        int sc = s - sr;
        int rr = sr, cc = sc;
        while (rr >= 0 && cc < m) {
            if (grid[0][rr][cc] == 0) {
                // if (s == 3) printf("failed at (%d, %d)\n", rr, cc);
                ok = 0;
                break;
            }
            rr--, cc++;
        }
        if (!ok) continue;
        for (int r = 0; r < n && ok; r++) {
            for (int c = 0; c < m; c++) {
                if (r + c == s) continue;
                int nr = r + (s - (r + c)), nc = c + (s - (r + c));
                if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
                    if (grid[0][r][c] != 1) {
                        // if (s == 3) printf("failed at (%d, %d)!\n", r, c);
                        ok = 0;
                        break;
                    }
                }
                else if (!(grid[0][r][c] ^ grid[0][nr][nc])) {
                    // if (s == 3) printf("failed at (%d, %d)!!\n", r, c);
                    ok = 0;
                    break;
                }
            }
        }
        int ec = min(m - 1, s);
        int er = s - ec;
        if (ok) {
            if (i == 0) ret = min(ret, ppi({sr, sc}, {er, ec}));
            else ret = min(ret, ppi({er, m - 1 - ec}, {sr, m - 1 - sc}));
        }
    }
    return ret;
}                    

int main() {
    int n, m;
    while (cin >> n >> m) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                char k;
                scanf(" %c", &k);
                grid[0][r][c] = grid[1][c][r] = (k == '#') ? 1 : 0;
            }
        }

        ppi sol = min(test_horizontal(n, m, 0), test_horizontal(m, n, 1));
        sol = min(sol, test_diagonal(n, m, 0));
        for (int rr = 0; rr < n; rr++)
            for (int l = 0, r = m - 1; l < r; l++, r--)
                swap(grid[0][rr][l], grid[0][rr][r]);
        sol = min(sol, test_diagonal(n, m, 1));
            
        printf("%d %d %d %d\n", sol.first.first + 1, sol.first.second + 1,
               sol.second.first + 1, sol.second.second + 1);
    }
        
    return 0;
}
