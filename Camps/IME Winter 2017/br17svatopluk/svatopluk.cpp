#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        lint n;
        cin >> n;
        lint ans = 0;
        lint a = 0, b = 0, c = n;

        for (int i = 60; i >= 0; i--) {
            lint test = ans | (1LL << i);
            if (3 * test > n) continue;
            lint target = n - 3 * test;
            vector<pll> knapsack;
            for (int j = 0; j < 60; j++) {
                if (test & (1LL << j)) continue;
                for (int k = 0; k < 3; k++)
                    knapsack.push_back(pll(1LL << j, k));
            }
            sort(knapsack.begin(), knapsack.end(), greater<pll>());
            lint la = test, lb = test, lc = test;
            for (pll p: knapsack) {
                lint x, i;
                tie(x, i) = p;                
                if (x <= target) {
                    target -= x;
                    if (i == 0) la |= x;
                    else if (i == 1) lb |= x;
                    else lc |= x;
                }                    
            }
            if (target == 0) {
                ans = test;
                a = la, b = lb, c = lc;
            }
        }
        printf("%lld %lld %lld\n", a, b, c);
    }        
    return 0;
}
