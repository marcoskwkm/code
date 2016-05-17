#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, a, b, c, d;
    scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
    lint ans = 0;
    for (int i = 1; i <= n; i++) {
        int s = i + a + b;
        if (s - a - c < 1 || s - a - c > n) continue;
        if (s - c - d < 1 || s - c - d > n) continue;
        if (s - b - d < 1 || s - b - d > n) continue;
        ans += n;
    }
    cout << ans << endl;
    return 0;
}
