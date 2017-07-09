#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    #ifndef HOME
    freopen("popcorn.in", "r", stdin);
    #endif
    int t;
    for (scanf("%d", &t); t--;) {
        int n, k;
        scanf("%d%d", &n, &k);
        lint ans = 1;
        for (int i = 0; i < k; i++)
            ans *= n - i;
        for (int i = 1; i <= k; i++)
            ans /= i;
        cout << ans << endl;
    }
    return 0;
}
