#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

int v[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]);
    int ans = 0;
    int last_cut = -1;
    for (int i = 0; i < n; i++) {
        int lim = v[i] - last_cut - 1;
        if (i + 1 < n) lim = min(lim, v[i + 1] - v[i] - 1);
        if (v[i] - lim - 1 != last_cut) ans++;
        last_cut = v[i] + lim;
        if (last_cut != m) ans++;
    }
    printf("%d\n", ans);        
    return 0;
}
