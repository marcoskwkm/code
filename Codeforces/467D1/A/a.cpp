#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    lint k, d, t;
    cin >> k >> d >> t;
    t *= 2;
    lint cycle = k;
    if (cycle % d) cycle += d - k % d;
    
    lint cycle_cook = 2 * k + cycle - k;
    lint ans = t / cycle_cook * cycle;
    t %= cycle_cook;

    // debug("cycle = %lld, cycle_cook = %lld, ans = %lld\n", cycle, cycle_cook, ans);

    if (t <= 2 * k) {
        printf("%lld", ans + t / 2);
        if (t & 1) printf(".5");
    }
    else {
        t -= 2 * k;
        printf("%lld", ans + k + t);
    }
    printf("\n");
    return 0;
}
