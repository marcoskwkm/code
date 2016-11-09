#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

int nim[MAXN];

int main() {
    #ifndef HOME
    freopen("powers.in", "r", stdin);
    #endif

    int t;
    for (scanf("%d", &t); t--;) {
        int x = 0;
        int q;
        for (scanf("%d", &q); q--;) {
            int b, n;
            scanf("%d%d", &b, &n);
            if (b & 1) x ^= (n & 1);
            else {
                int k = n % (b + 1);
                if (k == b) x ^= 2;
                else x ^= (k & 1);
            }
        }
        printf("%d\n", x ? 1 : 2);
    }        
    return 0;
}
