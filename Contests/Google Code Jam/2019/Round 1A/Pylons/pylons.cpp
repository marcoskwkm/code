#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 22;

int R, C;

bool grid[MAXN][MAXN];
pii sol[MAXN * MAXN];

bool go(int r, int c, int q) {
    sol[q] = pii(r, c);
    if (q == R * C - 1) return 1;
    vector<pii> avail;
    for (int nr = 0; nr < R; nr++) {
        for (int nc = 0; nc < C; nc++) {
            if (grid[nr][nc] || r == nr || c == nc || r - c == nr - nc || r + c == nr + nc)
                continue;
            avail.push_back(pii(nr, nc));
        }
    }
    random_shuffle(avail.begin(), avail.end());

    grid[r][c] = 1;
    for (pii nxt: avail)
        if (go(nxt.first, nxt.second, q + 1))
            return 1;

    grid[r][c] = 0;
    return 0;
}

int main() {
    srand(42); // Removing this results in TLE!!
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        cin >> R >> C;
        if (R == 2) {
            if (2 <= C && C <= 4) {
                printf("Case #%d: IMPOSSIBLE\n", t);
                continue;
            }
        }
        else if (R == 3) {
            if (2 <= C && C <= 3) {
                printf("Case #%d: IMPOSSIBLE\n", t);
                continue;
            }
        }
        else if (R == 4 && C == 2) {
            printf("Case #%d: IMPOSSIBLE\n", t);
            continue;
        }
                
        bool found = 0;
        for (int r = 0; r < R && !found; r++) {
            for (int c = 0; c < C && !found; c++) {
                if (go(r, c, 0)) {
                    memset(grid, 0, sizeof(grid));
                    found = 1;
                    break;
                }
            }
        }
        printf("Case #%d: %s\n", t, found ? "POSSIBLE" : "IMPOSSIBLE");
        if (found) {
            for (int i = 0; i < R * C; i++)
                printf("%d %d\n", sol[i].first + 1, sol[i].second + 1);
        }
        else debug("No solution for %d %d\n", R, C);
    }
        
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 22;

int R, C;

bool grid[MAXN][MAXN];
pii sol[MAXN][MAXN][MAXN * MAXN];
bool done[MAXN][MAXN];
pii avail[MAXN * MAXN][MAXN * MAXN];

pii starting_point[MAXN][MAXN];

bool go(int r, int c, int q) {
    sol[R][C][q] = pii(r, c);
    if (q == R * C - 1) return 1;

    int avail_cnt = 0;
    for (int nr = 0; nr < R; nr++) {
        for (int nc = 0; nc < C; nc++) {
            if (grid[nr][nc] || r == nr || c == nc || r - c == nr - nc || r + c == nr + nc)
                continue;
            avail[q][avail_cnt++] = pii(nr, nc);
        }
    }
    random_shuffle(avail[q], avail[q] + avail_cnt);

    grid[r][c] = 1;
    for (int i = 0; i < avail_cnt; i++)
        if (go(avail[q][i].first, avail[q][i].second, q + 1))
            return 1;

    grid[r][c] = 0;
    return 0;
}

int main() {
    srand(42);
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        cin >> R >> C;
        if (R == 2) {
            if (2 <= C && C <= 4) {
                printf("Case #%d: IMPOSSIBLE\n", t);
                continue;
            }
        }
        else if (R == 3) {
            if (2 <= C && C <= 3) {
                printf("Case #%d: IMPOSSIBLE\n", t);
                continue;
            }
        }
        else if (R == 4 && C == 2) {
            printf("Case #%d: IMPOSSIBLE\n", t);
            continue;
        }

        for (int r = 0; r < R && !done[R][C]; r++) {
            for (int c = 0; c < C && !done[R][C]; c++) {
                if (go(r, c, 0)) {
                    memset(grid, 0, sizeof(grid));
                    done[R][C] = 1;
                    starting_point[R][C] = pii(r, c);
                    break;
                }
            }
        }
        printf("Case #%d: POSSIBLE\n", t);
        for (int i = 0; i < R * C; i++)
            printf("%d %d\n", sol[R][C][i].first + 1, sol[R][C][i].second + 1);
    }
    
    return 0;
}
