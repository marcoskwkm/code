#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

int v[MAXN];

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);
        sort(v, v + n);
        int mid = n / 2;
        int ans;
        if (n & 1) {
            int low = -v[mid - 1] - v[mid];
            for (int i = 0; i < mid - 1; i++)
                low -= 2*v[i];
            for (int i = mid + 1; i < n; i++)
                low += 2*v[i];
            
            int hi = v[mid] + v[mid + 1];
            for (int i = 0; i < mid; i++)
                hi -= 2*v[i];
            for (int i = mid + 2; i < n; i++)
                hi += 2*v[i];

            ans = max(low, hi);
        }
        else {
            ans = v[mid] - v[mid - 1];
            for (int i = 0; i < mid - 1; i++)
                ans -= 2*v[i];
            for (int i = mid + 1; i < n; i++)
                ans += 2*v[i];
        }
        printf("Case %d: %d\n", t, ans);
    }        
    return 0;
}
