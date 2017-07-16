#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 32;

char grid[MAXN][MAXN];
int n;

void block(int r, int c) {
    grid[r][c] = 'x';
    for (int d = -1; d <= 1; d++) {
        int nr = r - 1, nc = c + d;
        if (grid[nr][nc] == '.') block(nr, nc);
    }
}

vector<pii> f;
bool seen[MAXN][MAXN];

void find(int r, int c) {
    f.push_back(pii(r, c));
    seen[r][c] = 1;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = r + dr, nc = c + dc;
            if (grid[nr][nc] == '.' && !seen[nr][nc])
                find(nr, nc);
        }
    }
}        

int main() {
    cin >> n;
    memset(grid, '#', sizeof(grid));
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= n; c++)
            scanf(" %c", &grid[r][c]);
    for (int r = 2; r <= n; r++) {
        if (grid[r][1] == '.') block(r, 1);
        if (grid[r][n] == '.') block(r, n);
    }
    for (int c = 2; c < n; c++)
        if (grid[n][c] == '.') block(n, c);

    for (int c = 1; c <= n; c++)
        if (grid[1][c] == '.')
            find(1, c);
    sort(f.begin(), f.end(), [](pii a, pii b) { return a.first > b.first; });

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
        grid[f[i].first][f[i].second] = '*';

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++)
            // printf("%c", grid[r][c]);
           printf("%c", grid[r][c] == 'x' ? '.' : grid[r][c]);
        printf("\n");
    }    
    return 0;
}
