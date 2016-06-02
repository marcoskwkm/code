#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int) 1e5 + 10;

int v[MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]);
    sort(v, v + n);
    int ans = k + 1;
    int r = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i == r) r++;
        while (r < n) {
            int needs = v[r] - v[i] - 1 - (r - i - 1);            
            if (needs <= k) ans = max(ans, v[r] - v[i] + 1 + (k - needs));
            else break;
            r++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
