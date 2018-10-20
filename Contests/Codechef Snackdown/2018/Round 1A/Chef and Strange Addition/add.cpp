#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int target;
lint dp[32][32][32][2];

lint go(int qa, int qb, int i, int carry) {
    if (i == 31) {
        if (qa == 0 && qb == 0 && carry == 0)
            return 1;
        else
            return 0;
    }
    if (dp[qa][qb][i][carry] != -1)
        return dp[qa][qb][i][carry];

    lint ret = 0;
    for (int a = 0; a <= min(qa, 1); a++) {
        for (int b = 0; b <= min(qb, 1); b++) {
            int bit = (target & (1 << i)) > 0;
            if (a ^ b ^ carry ^ bit) continue;
            ret += go(qa - a, qb - b, i + 1, a + b + carry > 1);
        }
    }
    return dp[qa][qb][i][carry] = ret;
}        

int main() {
    int t;
    for (cin >> t; t--;) {
        int a, b;
        cin >> a >> b >> target;
        memset(dp, -1, sizeof(dp));
        printf("%lld\n", go(__builtin_popcount(a), __builtin_popcount(b), 0, 0));
    }        
    return 0;
}
