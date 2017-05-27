#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int ans[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int k;
        scanf("%d", &k);
        int big = 21;
        int small = 1;
        int len = 0;
        for (int i = 19; i >= 0; i--) {
            bool take = 0;
            if (k >= (1 << i)) {
                k -= (1 << i);
                ans[len++] = small++;
                take = 1;
            }
            if (i) ans[len++] = big + 1;
            ans[len++] = big;
            big += 2;
            if (!take) ans[len++] = small++;            
        }
        printf("%d\n", len);
        for (int i = 0; i < len; i++)
            printf("%d%c", ans[i], " \n"[i + 1 == len]);
    }        
    return 0;
}
