#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

lint dp[10];
lint tmp[10];

int main() {
    int n;
    cin >> n;
    lint sum = 0;    
    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        lint val;
        scanf("%lld", &val);
        sum += val;
        int m = val % 7;
        for (int j = 0; j < 7; j++)
            tmp[(j + m) % 7] = min(dp[(j + m) % 7], dp[j] + val);
        for (int j = 0; j < 7; j++)
            dp[j] = tmp[j];            
    }
    printf("%lld\n", sum - dp[sum % 7]);    
    return 0;
}
