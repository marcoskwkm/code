#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int v[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d",&v[i]);
    sort(v + 1, v + n + 1);

    lint ans = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] == v[i - 1]) continue;
        lint got = lint(n - i + 1) * v[i];
        for (lint j = 2; j * v[i] <= v[n]; j++) {
            int idx = lower_bound(v + 1, v + n + 1, j * v[i]) - v;
            got += lint(n - idx + 1) * v[i];
        }
        ans = max(ans, got);
    }
    cout << ans << endl;    
    return 0;
}
