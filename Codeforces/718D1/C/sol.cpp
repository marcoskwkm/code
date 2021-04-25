#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

int m[MAXN][MAXN];
int cnt[MAXN];
set<pii> avail[MAXN];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cnt[i + 1] = i;
        scanf("%d", &m[i][i]);
        if (i == 0) {
            avail[m[i][i]].insert(pii(1, 0));
        } else if (i == n - 1) {
            avail[m[i][i]].insert(pii(n - 1, n - 2));
        } else {
            avail[m[i][i]].insert(pii(i, i - 1));
            avail[m[i][i]].insert(pii(i + 1, i));
        }
    }

    bool flag = 1;
    for (int i = 1; i < n && flag; i++) {
        for (int j = 0; j + i < n && flag; j++) {
            int worst = 1;
            for (int k = 2; k <= n; k++) {
                if (cnt[k] == 0) {
                    continue;
                }
                if (avail[k].size() < avail[worst].size() || cnt[worst] == 0) {
                    worst = k;
                }
            }
            if (avail[worst].empty()) {
                if (cnt[worst] > 0) {
                    flag = 0;
                    break;
                } else {
                    j--;
                    continue;
                }
            }
            auto [r, c] = *avail[worst].begin();
            cnt[worst]--;
            m[r][c] = worst;
            // debug("place %d at (%d, %d)\n", worst, r, c);

            for (int z = 0; z < 4; z++) {
                int nr = r + dr[z], nc = c + dc[z];
                if (nr < 0 || nc < 0 || nr >= n || nc >= n) {
                    continue;
                }
                if (m[nr][nc] > 0) {
                    avail[m[nr][nc]].erase(pii(r, c));
                } else if (m[nr][nc] == 0 && cnt[worst] > 0) {
                    avail[worst].insert(pii(nr, nc));
                }
            }
        }
    }

    if (!flag) {
        printf("-1\n");
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                printf("%d ", m[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
