#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

char grid[MAXN][MAXN];
vector<int> rows[MAXN], cols[MAXN];
char sol[MAXN][MAXN];

int main() {
    freopen("japanese.in", "r", stdin);
    freopen("japanese.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            scanf(" %c", &grid[r][c]);

    int rows_size = 0;
    for (int r = 0; r < n; r++) {
        int cnt = 0;
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == '.') {
                if (cnt > 0) rows[r].push_back(cnt);
                cnt = 0;
            }
            else cnt++;
        }
        if (cnt) rows[r].push_back(cnt);
        rows_size = max<int>(rows_size, rows[r].size());
    }

    int cols_size = 0;
    for (int c = 0; c < m; c++) {
        int cnt = 0;
        for (int r = 0; r < n; r++) {
            if (grid[r][c] == '.') {
                if (cnt > 0) cols[c].push_back(cnt);
                cnt = 0;
            }
            else cnt++;
        }
        if (cnt) cols[c].push_back(cnt);
        cols_size = max<int>(cols_size, cols[c].size());
    }

    memset(sol, '.', sizeof(sol));
    for (int r = 0; r < cols_size; r++)
        for (int c = 0; c < rows_size; c++)
            sol[r][c] = '*';
    for (int r = 0; r < n; r++) {
        int q = 0;
        for (int i = 0; i < rows_size; i++) {
            if (rows_size - i > rows[r].size())
                sol[r + cols_size][i] = '_';
            else
                sol[r + cols_size][i] = rows[r][q++] + '0';
        }
    }
    for (int c = 0; c < m; c++) {
        int q = 0;
        for (int i = 0; i < cols_size; i++) {
            if (cols_size - i > cols[c].size())
                sol[i][c + rows_size] = '_';
            else
                sol[i][c + rows_size] = cols[c][q++] + '0';
        }
    }

    for (int r = 0; r < n + cols_size; r++) {
        for (int c = 0; c < m + rows_size; c++)
            printf("%c", sol[r][c]);
        printf("\n");
    }
                    
    return 0;
}
