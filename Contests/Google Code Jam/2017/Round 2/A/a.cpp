#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int q[5];

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        memset(q, 0, sizeof(q));
        printf("Case #%d: ", t);
        int n, p;
        scanf("%d%d", &n, &p);
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            q[x % p]++;
        }
        int ans = q[0];
        if (p == 2) {
            ans += (q[1] + 1) / 2;
        }
        else if (p == 3) {
            int add = min(q[1], q[2]);
            ans += add;
            q[1] -= add; q[2] -= add;
            ans += (q[1] + 2) / 3;
            ans += (q[2] + 2) / 3;
        }   
        printf("%d\n", ans);
    }        
    return 0;
}
