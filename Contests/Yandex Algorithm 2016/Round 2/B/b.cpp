#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int cnt1(int n, int i) {
    n++;
    int ret = 0;
    if (i < 30) {
        int cycle = (1 << (i + 1));
        int ncycles = n / cycle;
        ret += ncycles * (1 << i);
        n %= cycle;
    }
    ret += max(0, n - (1 << i));
    return ret;
}

int main() {
    int l, r;
    scanf("%d%d", &l, &r);
    int ans = 0;
    for (int bit = 0; bit <= 30; bit++) {
        int q1 = cnt1(r, bit) - cnt1(l - 1, bit);
        int q0 = (r - l + 1) - q1;
        if (q1 == 0) continue;
        if (q1 > q0) ans |= (1 << bit);
    }
    printf("%d\n", ans);    
    return 0;
}
