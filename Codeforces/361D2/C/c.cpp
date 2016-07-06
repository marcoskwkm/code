#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint cnt(lint n) {
    lint ans = 0;
    for (lint k = 2; k*k*k <= n; k++) {
        ans += n / k / k / k;
    }
    return ans;
}
        
int main() {
    lint m;
    cin >> m;
    lint l = 8, r = (lint)1e18;
    while (l < r) {
        lint mid = (l + r)/2;
        if (cnt(mid) < m) l = mid + 1;
        else r = mid;
    }
    if (cnt(l) != m) printf("-1\n");
    else cout << l << endl;
    return 0;
}
