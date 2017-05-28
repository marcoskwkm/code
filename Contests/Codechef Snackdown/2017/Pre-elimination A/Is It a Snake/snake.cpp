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

char grid[2][MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        scanf("%s%s", grid[0], grid[1]);
        bool done = 0, started = 0;
        bool ok = 1;
        int mask = 3;
        for (int c = 0; c < n; c++) {
            int m = 0;
            for (int r: {0, 1})
                if (grid[r][c] == '#')
                    m += (1 << r);
            if (m == 0) {
                if (started) done = 1;
            }
            else {
                if (done) {
                    ok = 0;
                    break;
                }
                started = 1;
                if (m == 3) {
                    if (mask != 3) mask = 3 ^ mask;
                }
                else {
                    if ((mask & m) == 0) {
                        ok = 0;
                        break;
                    }
                    mask = m;
                }
            }
        }
        printf("%s\n", ok ? "yes" : "no");
    }            
    return 0;
}
