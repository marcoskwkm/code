#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, h, k;
    scanf("%d%d%d", &n, &h, &k);
    lint ans = 0;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        if (cur + p <= h) {
            cur += p;
            ans += cur / k;
            cur %= k;
        }
        else {
            ans++;
            ans += p / k;
            cur = p % k;
        }
    }
    if (cur) ans++;
    cout << ans << endl;        
    return 0;
}
