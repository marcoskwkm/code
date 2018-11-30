// O((LC)^2)

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110, MAXK = (int)1e5 + 10;

int grid[MAXN][MAXN];
int dist[MAXN][MAXN];
bool seen[MAXN][MAXN];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int N, M, K;

void dijkstra(int sr, int sc) {
    memset(dist, INF, sizeof(dist));
    dist[sr][sc] = 0;
    while (1) {
        int d = INF, nr, nc;
        for (int r = 0; r < N; r++)
            for (int c = 0; c < M; c++)
                if (!seen[r][c] && dist[r][c] < d)
                    d = dist[r][c], nr = r, nc = c;
        if (d == INF) break;
        seen[nr][nc] = 1;
        for (int i = 0; i < 4; i++) {
            int rr = nr + dr[i], cc = nc + dc[i];
            if (rr < 0 || cc < 0 || rr >= N || cc >= M || seen[rr][cc])
                continue;
            if (grid[rr][cc] == -1 || (d + 1) % K == grid[rr][cc])
                dist[rr][cc] = min(dist[rr][cc], d + 1);
            else if (grid[nr][nc] == -1) {
                int t = (grid[rr][cc] - d) % K;
                if (t <= 0) t += K;
                dist[rr][cc] = min(dist[rr][cc], d + t);
            }
        }
    }
}

int main() {
    cin >> N >> M >> K;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            scanf("%d", &grid[r][c]);
    dijkstra(0, 0);
    printf("%d\n", seen[N - 1][M - 1] ? dist[N - 1][M - 1] : -1);
    return 0;
}
