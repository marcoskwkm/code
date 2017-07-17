#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

bool expected[MAXN];

int main() {
    int n;
    while (cin >> n) {
        memset(expected, 0, sizeof(expected));
        int n_seq = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            if (!expected[x]) n_seq++;
            expected[x + 1] = 1;
        }
        int ans = 0;
        while ((1 << ans) < n_seq) ans++;
        printf("%d\n", ans);
    }        
    return 0;
}
