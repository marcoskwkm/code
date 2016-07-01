#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int qh = 0, qm = 0;
    int nn = n - 1, mm = m - 1;
    while (nn) {
        nn /= 7;
        qh++;
    }
    while (mm) {
        mm /= 7;
        qm++;
    }
    qh = max(qh, 1); qm = max(qm, 1);
    if (qh + qm > 7) printf("0\n");
    else {
        int ans = 0;
        int d[7];
        for (int i = 0; i < n; i++) {
            nn = i;
            memset(d, 0, sizeof(d));
            bool ok = 1;
            for (int k = 0; k < qh; k++) {
                if (++d[nn % 7] > 1) {
                    ok = 0;
                }
                nn /= 7;
            }
            if (!ok) continue;                
            for (int j = 0; j < m; j++) {
                mm = j;
                int dm[7];
                memset(dm, 0, sizeof(dm));
                bool ok2 = 1;
                for (int k = 0; k < qm; k++) {
                    if (++dm[mm % 7] + d[mm % 7] > 1) {
                        ok2 = 0;
                    }
                    mm /= 7;
                }
                if (ok2) {
                    // printf("%d, %d\n", i, j);
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }                
    return 0;
}
