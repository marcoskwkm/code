#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> Move;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 20;

char grid[MAXN][MAXN];

pii find(char k, int n, int m) {
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= m; c++)
            if (grid[r][c] == k)
                return pii(r, c);
}

void move(int sr, int sc, int tr, int tc, vector<Move> &v) {
    int dr = sr < tr ? 1 : -1;
    for (; sr != tr; sr += dr) {
        if (grid[sr][sc] == grid[sr + dr][sc]) continue;
        if (grid[sr][sc] == '.')
            v.push_back(Move(sr + dr, sc, sr, sc));
        else
            v.push_back(Move(sr, sc, sr + dr, sc));
        swap(grid[sr][sc], grid[sr + dr][sc]);
    }
    int dc = sc < tc ? 1 : -1;
    for (; sc != tc; sc += dc) {
        if (grid[sr][sc] == grid[sr][sc + dc]) continue;
        if (grid[sr][sc] == '.')
            v.push_back(Move(sr, sc + dc, sr, sc));
        else
            v.push_back(Move(sr, sc, sr, sc + dc));
        swap(grid[sr][sc], grid[sr][sc + dc]);
    }
}

void solve_row(int r, int n, int m, vector<Move> &v) {
    for (int c = 3; c <= m; c++) {
        if (grid[r][c] == '.') break;
        move(r, c, r, 3, v);
        v.push_back(Move(r, 3, r, 1));
        v.push_back(Move(r, 1, r, 2));
        grid[r][3] = '.';
    }
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        bool flip = 0;
        if (m < 3) flip = 1;
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= m; c++)
                scanf(" %c", &grid[r][c]);
        if ((n == 2 && m == 2) || (n == 1 && m == 1)) {
            printf("-1\n");
            continue;
        }
        if (n <= 2 && m <= 2) {
            printf("0\n");
            continue;
        }
        if (flip) {
            for (int r = 1; r <= n; r++)
                for (int c = 1; c < r; c++)
                    swap(grid[r][c], grid[c][r]);
            swap(n, m);
        }
        int sr, sc;
        tie(sr, sc) = find('.', n, m);
        vector<Move> sol;
        move(sr, sc, 1, 1, sol);
        solve_row(1, n, m, sol);
        int cur = 3;
        for (int r = 2; r <= n; r++) {
            move(r, 1, 1, 1, sol);
            move(1, cur, 1, 1, sol);
            if (cur == m) {
                solve_row(1, n, m, sol);
                cur = 3;
            }
            else cur++;
            solve_row(r, n, m, sol);
            move(r, 2, r, 1, sol);
            move(r, 1, 1, 1, sol);
            move(1, cur, 1, 1, sol);
            if (cur == m) {
                solve_row(1, n, m, sol);
                cur = 3;
            }
            else cur++;
        }
        if (cur > 3) solve_row(1, n, m, sol);
        printf("%d\n", (int)sol.size());
        for (auto mov: sol) {
            if (flip) printf("%d %d %d %d\n", get<1>(mov), get<0>(mov), get<3>(mov), get<2>(mov));
            else printf("%d %d %d %d\n", get<0>(mov), get<1>(mov), get<2>(mov), get<3>(mov));
        }
    }        
    return 0;
}
