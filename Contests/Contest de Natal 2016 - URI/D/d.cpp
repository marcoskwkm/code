#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 1010;

char grid[MAXD][MAXD];
int dist[MAXD][MAXD];
int cmp[MAXD][MAXD];
int cmp_size[MAXD * MAXD];
int cmp_dist[MAXD * MAXD];
int n, m;

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

int dfs_dots(int r, int c, int k) {
    int ret = 1;
    cmp[r][c] = k;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
        if (grid[nr][nc] == '.' && cmp[nr][nc] == -1)
            ret += dfs_dots(nr, nc, k);
    }
    return ret;
}

int main() {
    int t = 1;
    while (scanf("%d%d", &n, &m) > 0) {
        if (t > 1) printf("\n");
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                scanf(" %c", &grid[r][c]);
        memset(cmp, -1, sizeof(cmp));
        int largest = 0;
        int ncmp = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == '.' && cmp[r][c] == -1) {
                    cmp_size[ncmp] = dfs_dots(r, c, ncmp);
                    if (cmp_size[largest] < cmp_size[ncmp])
                        largest = ncmp;
                    ncmp++;
                }
            }
        }
        memset(dist, -1, sizeof(dist));
        memset(cmp_dist, INF, sizeof(cmp_dist));
        deque<pii> fila;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (cmp[r][c] == largest) {
                    dist[r][c] = 0;
                    fila.push_back(pii(r, c));
                }
            }
        }
        while (!fila.empty()) {
            int r, c;
            tie(r, c) = fila.front();
            fila.pop_front();
            cmp_dist[cmp[r][c]] = min(cmp_dist[cmp[r][c]], dist[r][c]);
            if (cmp_size[cmp[r][c]] == 1) continue;
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if (grid[nr][nc] == '#') continue;
                if (dist[nr][nc] == -1) {
                    // if (grid[nr][nc] == '.' && grid[r][c] == '.') {
                    //     dist[nr][nc] = dist[r][c];
                    //     fila.push_front(pii(nr, nc));
                    // }
                    // else {
                    dist[nr][nc] = dist[r][c] + 1;
                    fila.push_back(pii(nr, nc));
                    // }
                }
            }
        }

        lint dist_sum = 0, light_sum = 0;
        bool ok = 1;
        for (int i = 0; i < ncmp; i++) {
            if (cmp_dist[i] == INF) {
                ok = 0;
                break;
            }
            if (i == largest) continue;
            // printf("%d %d\n", cmp_dist[i], cmp_size[i]);
            dist_sum += cmp_dist[i] - 1;
            light_sum += cmp_size[i] * lint(cmp_dist[i] - 1);
        }
        printf("Instance #%02d:\n", t++);
        if (!ok) printf("Network Error\n");
        else printf("%d %lld %lld\n", cmp_size[largest], dist_sum, light_sum);
    }        
    return 0;
}
