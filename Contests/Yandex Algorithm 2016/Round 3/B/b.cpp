#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;
const int MAXK = (int)1e6 + 10;

lint pow2[MAXK];

int main() {
    pow2[0] = 1;
    for (int i = 1; i < MAXK; i++)
        pow2[i] = (2 * pow2[i - 1]) % MOD;
    
    int n, k;
    scanf("%d%d", &n, &k);
    lint ans = 1;
    for (int len = 1; len <= k; len++) {
        int any = max(0, len - 2);
        ans += pow2[any] * (n - len + 1) % MOD;
    }
    
    printf("%d\n", ans % MOD);    
    return 0;
}
