#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210;

char grid[MAXN][MAXN];
int last[MAXN][MAXN][MAXN];
char seq[MAXN];
char dir[] = "^>v<";
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    int n;
    while(scanf("%d", &n) > 0 && n) {
        scanf(" %s", seq);
        int len = strlen(seq);
        int sr = 0, sc = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == 'R') {
                    grid[r][c] = '.';
                    sr = r; sc = c;
                }
                for (int t = 0; t < len; t++)
                    last[r][c][t] = -1;
            }
        }
        int t = 0;
        bool finished = 0;
        vector<pii> trail;
        trail.push_back(pii(sr, sc));
        int cycle = -1;
        while (!finished) {
            for (int i = 0; i < len; i++) {
                if (last[sr][sc][i] != -1) {
                    finished = 1;
                    cycle = t - last[sr][sc][i];
                    break;
                }
                else {
                    last[sr][sc][i] = t;
                }
                int nr = sr, nc = sc;
                for (int j = 0; j < 4; j++) {
                    if (seq[i] == dir[j]) {
                        nr += dr[j], nc += dc[j];
                    }
                }
                if (grid[nr][nc] != '#') {
                    sr = nr; sc = nc;
                    trail.push_back(pii(sr, sc));
                    t++;
                }
            }
        }
        if (cycle == 0) printf("1\n");
        else {
            // printf("trail:");
            // for (pii p: trail) printf(" (%d, %d),", p.first, p.second);
            // printf("\n");
            vector<pii> v;
            for (int i = 0; i < cycle; i++)
                v.push_back(trail[trail.size() - 1 - cycle + i]);
            // printf("cycle:");
            // for (pii p: v) printf(" (%d, %d),", p.first, p.second);

            // printf("\n");
            int ans = INF;
            for (int d = 2; d*d <= cycle; d++) {
                if (cycle % d) continue;
                int k = d;
                for (int rep = 0; rep < 2; rep++) {
                    bool ok = 1;
                    for (int i = 0; i < cycle; i++)
                        if (v[i] != v[i % k])
                            ok = 0;
                    if (ok) ans = min(ans, k);
                    k = cycle / d;
                }
            }
            if (ans == INF) ans = cycle;
            printf("%d\n", ans);
        }
    }    
    return 0;
}
