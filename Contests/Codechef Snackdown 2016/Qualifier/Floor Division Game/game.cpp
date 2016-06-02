#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int main() {
    int t;
    vector<pll> v;
    v.push_back(pll(0, 0));
    lint cur = 1, prev = 0;
    int nim = 1;
    while (cur <= (lint)1e18 + 10) {
        v.push_back(pll(cur, nim));
        if (nim == 3) {
            lint tmp = cur;
            cur += prev;
            prev = tmp;
        }
        else {
            prev = cur;
            cur *= 2;
        }
        nim = (nim + 1) % 4;
    }
    reverse(v.begin(), v.end());
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        lint x = 0;
        for (int i = 0; i < n; i++) {
            lint a;
            scanf("%lld", &a);
            x ^= lower_bound(v.begin(), v.end(), pll(a, 10), greater<pll>())->second;
        }
        printf("%s\n", x ? "Henry" : "Derek");
    }    
    return 0;
}
