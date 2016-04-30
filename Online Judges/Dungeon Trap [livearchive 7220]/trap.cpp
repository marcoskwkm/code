#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef pair<int, pii> pip;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

char grid[MAXN][MAXN];
int n, m;
int dist[2][MAXN][MAXN];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

void dijkstra(int sr, int sc, int k) {
    set<pip> pq;
    dist[k][sr][sc] = 0;
    pq.insert(pip(dist[k][sr][sc], pii(sr, sc)));
    while (!pq.empty()) {
        int r, c;
        tie(r, c) = pq.begin()->second;
        pq.erase(pq.begin());
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= n || nc >= m || nr < 0 || nc < 0) continue;
            if (grid[nr][nc] == '0') continue;
            int cost = grid[nr][nc] - '0';
            if (grid[nr][nc] == 'B' || grid[nr][nc] == 'A') cost = 0;
            int got = dist[k][r][c] + cost;
            if (dist[k][nr][nc] > got) {
                pq.erase(pip(dist[k][nr][nc], pii(nr, nc)));
                dist[k][nr][nc] = got;
                pq.insert(pip(dist[k][nr][nc], pii(nr, nc)));
            }
        }
    }
}

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        scanf("%d%d", &n, &m);
        int sr, sc, er, ec;
        int total = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == 'A') sr = r, sc = c;
                else if (grid[r][c] == 'B') er = r, ec = c;
                else total += grid[r][c] - '0';
            }
        }
        int ans = -1;
        memset(dist, INF, sizeof(dist));
        dijkstra(sr, sc, 0);
        dijkstra(er, ec, 1);
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if ('1' <= grid[r][c] && grid[r][c] <= '9') {
                    if (dist[0][r][c] == INF || dist[1][r][c] == INF) continue;
                    ans = max(ans, total - dist[0][r][c] - dist[1][r][c] + 2*(grid[r][c] - '0'));
                }
            }
        }

        printf("Case #%d: %d\n", t, ans == -1 ? 0 : ans);
    }
    return 0;
}
