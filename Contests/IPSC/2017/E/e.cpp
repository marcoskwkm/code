#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int OFF = 200000;
const int MOD = (int)1e9 + 9;

int v[1000000];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        memset(v, 0, sizeof(v));
        int n;
        scanf("%d", &n);
        lint ans = 0;
        for (int i = 1; i <= n; i++) {
            int x, e;
            scanf("%d%d", &x, &e);
            x += OFF;
            lint cost = 1;
            if (e > 0) {
                v[x]++;
                for (int j = 1; v[x + j] - v[x + j - 1] < -1; j++)
                    v[x + j]++, cost++;
                for (int j = 1; v[x - j] - v[x - j + 1] < -1; j++)
                    v[x - j]++, cost++;
            }
            else {
                v[x]--;
                for (int j = 1; v[x + j] - v[x + j - 1] > 1; j++)
                    v[x + j]--, cost++;
                for (int j = 1; v[x - j] - v[x - j + 1] > 1; j++)
                    v[x - j]--, cost++;
            }
            ans += cost * i;
        }
        printf("%lld\n", ans % MOD);
    }            
    return 0;
}
