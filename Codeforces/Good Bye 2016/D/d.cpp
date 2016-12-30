#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 1010;

int grid[MAXD][MAXD];
int v[100];
int n;
int dr[] = {1, 1};
int dc[] = {0, 1};

void go(int i, int sr, int sc) {
    if (i == n) return;
    int r = sr, c = sc;
    for (int j = 0; j < v[i]; j++) {
        grid[r][c] = i + 1;
        if (j + 1 < v[i]) r += dr[i & 1], c += dc[i & 1];
    }
    go(i + 1, r + dr[(i + 1) & 1], c + dc[(i + 1) & 1]);
    for (int rr = 0; rr < MAXD; rr++) {
        for (int cc = 0; cc < MAXD; cc++) {
            int rrr, ccc;
            if (i & 1) {
                int dif = sr - sc;
                int dif3 = 2 * dif - (rr - cc);
                int sum3 = rr + cc;
                rrr = (sum3 + dif3) / 2;
                ccc = (sum3 - dif3) / 2;
            }               
            else rrr = rr, ccc = 2 * sc - cc;
            if (rrr < 0 || ccc < 0 || rrr >= MAXD || ccc >= MAXD) continue;
            int val = max(grid[rr][cc], grid[rrr][ccc]);
            if (val > i + 1) grid[rr][cc] = grid[rrr][ccc] = max(grid[rr][cc], grid[rrr][ccc]);
        }
    }
}            

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    go(0, 500, 500);
    int ans = 0;
    for (int r = 0; r < MAXD; r++) {
        for (int c = 0; c < MAXD; c++) {
            ans += (grid[r][c] > 0);
            // if (grid[r][c] > 0) {
            //     printf("(%d, %d) = %d\n", r - 500, c - 500, grid[r][c]);
            // }
        }
    }
    printf("%d\n", ans);
    return 0;
}
