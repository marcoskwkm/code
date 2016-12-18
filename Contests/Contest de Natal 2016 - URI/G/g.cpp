#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAXN = 22, MAXM = (int)1e5 + 10;

pii grid[MAXN][MAXM];
int order[MAXN];
int id[300];

int main() {
    int n, m;
    id['R'] = 3;
    id['W'] = 2;
    id['G'] = 1;
    id['S'] = 0;
    int t = 1;
    while (scanf("%d%d", &n, &m) > 0) {
        if (t > 1) printf("\n");
        lint total_red = 0;
        for (int r = 0; r < n; r++) {
            order[r] = r;
            for (int c = 0; c < m; c++) {
                int sz;
                char color;
                scanf(" %*c%d %*c %c", &sz, &color);
                if (color == 'R') total_red += sz;
                grid[r][c] = pii(id[color], sz);
            }
        }
        int ans = 0;
        for (int c = 0; c < m; c++) {
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - 1; j++) {
                    if (grid[order[j]][c] > grid[order[j + 1]][c]) {
                        swap(order[j], order[j + 1]);
                        ans++;
                    }
                }
            }
        }
        printf("Instance %02d:\n%d %lld\n", t++, ans, total_red);
    }
    return 0;
}
