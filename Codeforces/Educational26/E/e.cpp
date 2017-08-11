#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint gcd(lint a, lint b) { return b ? gcd(b, a % b) : a; }

int main() {
    lint a, b;
    cin >> a >> b;

    vector<lint> f;
    lint aa = a;
    for (lint d = 2; d * d <= aa; d++) {
        if (aa % d == 0) {
            do {
                aa /= d;
            } while (aa % d == 0);
            f.push_back(d);
        }
    }
    if (aa > 1) f.push_back(aa);
    
    lint ans = 0;
    while (b > 0) {
        lint d = gcd(a, b);
        a /= d, b /= d;
        lint nxtb = 0;
        for (lint d: f) {
            if (a % d) continue;
            nxtb = max(nxtb, b - b % d);
        }
        ans += b - nxtb;
        b = nxtb;
    }

    cout << ans << endl;        
    return 0;
}
