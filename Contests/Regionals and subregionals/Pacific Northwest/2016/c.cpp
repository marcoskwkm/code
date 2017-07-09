#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int v[MAXN];

int main() {
    int n, k, r;
    scanf("%d%d%d", &n, &k, &r);
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        v[x] = 1;
    }
    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < r; i++)
        cnt += v[i];
    for (int i = r - 1; cnt < 2; i--) {
        if (v[i] == 0) {
            v[i] = 1;
            cnt++;
            ans++;
        }
    }
    for (int i = r; i < n; i++) {
        cnt += v[i] - v[i - r];
        if (cnt < 2) {
            v[i] = 1;
            cnt++;
            ans++;
        }
    }

    printf("%d\n", ans);        
    return 0;
}
