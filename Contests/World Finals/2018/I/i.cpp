#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXR = 6010, MAXC = 12010;

char grid[MAXR][MAXC];
int maxl[MAXR][MAXC], maxr[MAXR][MAXC];
char buff[MAXC];
int bit[MAXC / 2];

void update(int i, int val) {
    for (i++; i < MAXC / 2; i += i & -i)
        bit[i] += val;
}

int query(int i) {
    int ret = 0;
    for (i++; i > 0; i -= i & -i)
        ret += bit[i];
    return ret;
}

int main() {
    int r, c;
    cin >> r >> c;
    int R = 2*r - 1, C = 2*c - 1;
    fgets(grid[0], MAXC, stdin);
    for (int i = 0; i < R; i++) {
        fgets(grid[i], MAXC, stdin);
        int len = strlen(grid[i]);
        grid[i][len - 1] = 0;
        for (int j = len - 1; j < C; j++)
            grid[i][j] = ' ';
        grid[i][C] = 0;
    }
    lint ans = 0;

    for (int step = 0; step < 2; step++) {
        memset(maxl, 0, sizeof(maxl));
        memset(maxr, 0, sizeof(maxr));
        for (int i = 2; i < R; i += 2) {
            int j = 0;
            while (j < C && grid[i][j] != 'x') j++;
            for (; j < C; j += 4) {
                if (j > 0 && grid[i - 1][j - 1] == '\\')
                    maxl[i][j] = maxl[i - 2][j - 2] + 1;
                if (j + 1 < C && grid[i - 1][j + 1] == '/')
                    maxr[i][j] = maxr[i - 2][j + 2] + 1;
            }
        }

        // for (int i = 0; i < R; i++) {
        //     for (int j = 0; j < C; j++) {
        //         if (grid[i][j] == 'x') printf("%d", maxl[i][j]);
        //         else printf("%c", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("---------\n");
        // for (int i = 0; i < R; i++) {
        //     for (int j = 0; j < C; j++) {
        //         if (grid[i][j] == 'x') printf("%d", maxr[i][j]);
        //         else printf("%c", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("---------\n");
        // for (int i = 0; i < R; i++) {
        //     for (int j = 0; j < C; j++) {
        //         if (grid[i][j] == 'x') printf("%d", maxh[i][j]);
        //         else printf("%c", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("---------\n");

        for (int i = 2; i < R; i += 2) {
            memset(bit, 0, sizeof(bit));
            multiset<pii> rs;
            int delta = 0;
            int j = 0;
            while (j < C && grid[i][j] != 'x') j++;
            for (; j < C; j += 4) {
                if (j > 0 && grid[i][j - 1] != '-') {
                    while (!rs.empty()) {
                        update(rs.begin()->second, -1);
                        rs.erase(rs.begin());
                    }
                    delta = 0;
                }
                while (!rs.empty() && rs.begin()->first <= delta) {
                    update(rs.begin()->second, -1);
                    rs.erase(rs.begin());
                }
                ans += query(j / 4) - query(j / 4 - maxl[i][j] - 1);
                delta++;
                rs.insert(pii(maxr[i][j] + delta, j / 4));
                update(j / 4, 1);
            }
        }                
        
        int i = 0, j = R - 1;
        for (; i < j; i++, j--) {
            strcpy(buff, grid[i]);
            strcpy(grid[i], grid[j]);
            strcpy(grid[j], buff);
            reverse(grid[i], grid[i] + C);
            reverse(grid[j], grid[j] + C);
        }
        if (i == j) reverse(grid[i], grid[i] + C);
    }
    printf("%lld\n", ans);
    return 0;
}
