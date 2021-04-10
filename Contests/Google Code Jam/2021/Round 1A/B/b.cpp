#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef unsigned long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int N_PRIMES = 95;
const int MAXM = 100;
const int MAXS = 50000;

int m;
int p[MAXM], e[MAXM];

lint go(lint prod, lint sum, int i) {
    if (prod > sum) {
        return 0;
    }
    if (i == m) {
        return prod == sum ? prod : 0;
    }
    lint ans = 0;
    for (int take = 0; take <= e[i]; take++) {
        ans = max(ans, go(prod, sum, i + 1));
        if (prod * p[i] <= MAXS) {
            prod *= p[i];
            sum -= p[i];
        } else {
            break;
        }
    }
    return ans;
}

void solve() {
    cin >> m;
    lint sum = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &p[i], &e[i]);
        sum += p[i] * e[i];
    }
    printf(" %lld\n", go(1, sum, 0));
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        solve();
    }
    return 0;
}
