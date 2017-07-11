#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

int main() {
    int n;
    cin >> n;
    lint ans = 0;
    lint pow2 = 1;
    for (int i = 0; i < n - 1; i++)
        pow2 = (pow2 * 2) % MOD;
    for (int i = 0; i < n; i++) {
        lint x;
        scanf("%lld", &x);
        ans += x;
        ans %= MOD;
    }
    ans = ((ans * (pow2 - 1)) % MOD + MOD) % MOD;
    cout << ans << endl;        
    return 0;
}
