#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef pair<int, tiii> State;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55;

char grid[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN];
char s[MAXN];
int n, m, k;
int er, ec;

char dir[] = "UDLR";
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void dijkstra(int sr, int sc) {
    dp[sr][sc][0] = 0;
    set<State> pq;
    pq.insert(State(0, tiii(sr, sc, 0)));
    while (!pq.empty()) {
        int r, c, i;
        tie(r, c, i) = pq.begin()->second;
        pq.erase(pq.begin());
        if (i < k && dp[r][c][i + 1] > dp[r][c][i] + 1) {
            pq.erase(State(dp[r][c][i + 1], tiii(r, c, i + 1)));
            dp[r][c][i + 1] = dp[r][c][i] + 1;
            pq.insert(State(dp[r][c][i + 1], tiii(r, c, i + 1)));
        }
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nc < 0 || nr >= n || nc >= m || grid[nr][nc] == '#')
                nr = r, nc = c;
            if (i < k && dir[d] == s[i]) {
                if (dp[nr][nc][i + 1] > dp[r][c][i]) {
                    pq.erase(State(dp[nr][nc][i + 1], tiii(nr, nc, i + 1)));
                    dp[nr][nc][i + 1] = dp[r][c][i];
                    pq.insert(State(dp[nr][nc][i + 1], tiii(nr, nc, i + 1)));
                }
            }
            else {
                if (dp[nr][nc][i] > dp[r][c][i] + 1) {
                    pq.erase(State(dp[nr][nc][i], tiii(nr, nc, i)));
                    dp[nr][nc][i] = dp[r][c][i] + 1;
                    pq.insert(State(dp[nr][nc][i], tiii(nr, nc, i)));
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int sr, sc;
    for (int r = 0; r < n; r++) {
        scanf("%s", grid[r]);
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == 'R')
                sr = r, sc = c;
            if (grid[r][c] == 'E')
                er = r, ec = c;
        }
    }
    scanf("%s", s);
    k = strlen(s);
    memset(dp, INF, sizeof(dp));
    dijkstra(sr, sc);
    int ans = INF;
    for (int i = 0; i <= k; i++)
        ans = min(ans, dp[er][ec][i]);
    printf("%d\n", ans);
    return 0;
}
