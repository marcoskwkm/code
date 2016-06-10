#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 8, MAXK = 20;
const int MAXV = (int)5e5 + 10;

int v[MAXN];
int n;
int ans = INF;
int cur = 0;
bool sieve[MAXV];
vector<int> divs[MAXV];

void go(int last) {
    int taken[MAXN];
    int hi = 0;
    for (int j = 0; j < n; j++) {
        taken[j] = v[j] / last;
        cur += taken[j];
        v[j] -= last * taken[j];
        hi = max(hi, v[j]);
    }
    if (cur < ans) {
        if (last == 1) ans = min(ans, cur);
        else {
            for (int d: divs[last]) {
                go(d);
            }
        }
    }

    for (int j = 0; j < n; j++) {
        cur -= taken[j];
        v[j] += last * taken[j];
    }
}

int main() {
    for (int d = 2; d < MAXV; d++) {
        if (sieve[d]) continue;
        for (int m = d; m < MAXV; m += d) {
            sieve[m] = 1;
            divs[m].push_back(m / d);
        }
    }
    
    for (int i = 2; i < MAXV; i++)
        reverse(divs[i].begin(), divs[i].end());
    
    scanf("%d", &n);
    int hi = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        hi = max(hi, v[i]);
    }
    
    for (int i = hi; i >= 1; i--)
        go(i);
    
    printf("%d\n", ans);
    return 0;
}
