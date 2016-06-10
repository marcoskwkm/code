#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

char grid[MAXN][MAXN];
int n, k;
int component[MAXN][MAXN];
int size[MAXN*MAXN];
int orig_size[MAXN*MAXN];
int last_taken[MAXN*MAXN];

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

inline bool valid(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

void dfs(int r, int c, int cmp) {
    component[r][c] = cmp;
    size[cmp]++;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (!valid(nr, nc)) continue;
        if (component[nr][nc] != -1 || grid[nr][nc] == 'X') continue;
        dfs(nr, nc, cmp);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            scanf(" %c", &grid[r][c]);
    memset(component, -1, sizeof(component));
    int cnt = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == '.' && component[r][c] == -1) {
                dfs(r, c, cnt);
                orig_size[cnt] = size[cnt];
                cnt++;
            }
        }
    }
    int best = 0;
    int t = 1;
    for (int r = 0; r + k - 1 < n; r++) {
        for (int i = 0; i < cnt; i++)
            size[i] = orig_size[i];
        for (int rr = 0; rr < k; rr++)
            for (int cc = 0; cc < k; cc++)
                if (grid[r + rr][cc] == '.')
                    size[component[r + rr][cc]]--;
        for (int c = 0; c + k - 1 < n; c++) {
            int got = k * k;
            for (int i = 0; i < k; i++) {
                int rr, cc;
                rr = r - 1, cc = c + i;
                if (valid(rr, cc) && grid[rr][cc] == '.' && last_taken[component[rr][cc]] != t) {
                    got += size[component[rr][cc]];
                    last_taken[component[rr][cc]] = t;
                }
                rr = r + i, cc = c + k;
                if (valid(rr, cc) && grid[rr][cc] == '.' && last_taken[component[rr][cc]] != t) {
                    got += size[component[rr][cc]];
                    last_taken[component[rr][cc]] = t;
                }
                rr = r + k, cc = c + i;
                if (valid(rr, cc) && grid[rr][cc] == '.' && last_taken[component[rr][cc]] != t) {
                    got += size[component[rr][cc]];
                    last_taken[component[rr][cc]] = t;
                }
                rr = r + i, cc = c - 1;
                if (valid(rr, cc) && grid[rr][cc] == '.' && last_taken[component[rr][cc]] != t) {
                    got += size[component[rr][cc]];
                    last_taken[component[rr][cc]] = t;
                }
            }
            best = max(best, got);
            for (int rr = r; rr < r + k; rr++) {
                if (grid[rr][c] == '.')
                    size[component[rr][c]]++;
                if (c + k < n && grid[rr][c + k] == '.')
                    size[component[rr][c + k]]--;
            }
            t++;
        }
    }
    printf("%d\n", best);    
    return 0;
}
