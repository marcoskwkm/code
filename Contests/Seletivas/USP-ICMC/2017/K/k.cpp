#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = 22;

lint q[1 << MAXM];
lint dp[1 << MAXM];
int foo[MAXM];

int main() {
    lint n, m;
    cin >> n >> m;
    lint ans = n * (n - 1) / 2;
    map<int, int> f;    
    int low = INF;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        q[x]++;
        low = min(low, x);
    }
    memset(dp, -1, sizeof(dp));
    for (int mask = 0; mask < (1 << m); mask++) {
        if (q[mask] == 0) continue;
        ans -= q[mask] * (q[mask] - 1) / 2;
        if (mask > 0) ans -= q[mask] * q[0];
        int submask = mask;
        int sum = 0;
        while (submask > 0 && submask >= low) {
            if (submask < mask && q[submask] > 0)
                sum += q[submask];
            submask = (submask - 1) & mask;
        }
        ans -= q[mask] * sum;
    }
    cout << ans << endl;    
    return 0;
}
