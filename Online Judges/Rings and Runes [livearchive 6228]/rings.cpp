#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = 110;

int runes[MAXM][3];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        bool has_null = 0;
        bool missing_ring = 0;
        bool repeated_ring = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d%*d", &runes[i][0], &runes[i][1], &runes[i][2]);
            if (runes[i][0] == 0 || runes[i][1] == 0 || runes[i][2] == 0)
                has_null = 1;
            if (runes[i][0] < -n || runes[i][0] > n ||
                runes[i][1] < -n || runes[i][1] > n ||
                runes[i][2] < -n || runes[i][2] > n)
                missing_ring = 1;
            if (abs(runes[i][0]) == abs(runes[i][1]) ||
                abs(runes[i][0]) == abs(runes[i][2]) ||
                abs(runes[i][1]) == abs(runes[i][2]))
                repeated_ring = 1;
        }
        if (has_null) printf("INVALID: NULL RING\n");
        else if (missing_ring) printf("INVALID: RING MISSING\n");
        else if (repeated_ring) printf("INVALID: RUNE CONTAINS A REPEATED RING\n");
        else {
            bool found = 0;
            for (int mask = 0; mask < (1 << n); mask++) {
                bool ok = 1;
                for (int i = 0; i < m; i++) {
                    bool sat = 0;
                    for (int j = 0; j < 3; j++) {
                        if (runes[i][j] < 0 && !(mask & (1 << (-runes[i][j] - 1)))) sat = 1;
                        if (runes[i][j] > 0 && (mask & (1 << (runes[i][j] - 1)))) sat = 1;
                    }
                    if (!sat) ok = 0;
                }
                if (ok) {
                    printf("RUNES SATISFIED!\n");
                    found = 1;
                    break;
                }
            }
            if (!found) printf("RUNES UNSATISFIABLE! TRY ANOTHER GATE!\n");
        }
    }
    return 0;
}
