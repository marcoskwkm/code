#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int LOG = 20;

int rmq[2][LOG][MAXN];
int v[2][MAXN];
int n;

// Builds RMQ structure for array v of size n in O(n*log(n))
void build_rmq(int k) {
    for(int i = 0; i < n; i++)
        rmq[k][0][i] = v[k][i];
    for(int log = 1; log < LOG; ++log) {
        for(int i = 0; i < n; i++) {
            if (k == 0)
                rmq[k][log][i] = min(rmq[k][log-1][i], rmq[k][log-1][min(n-1, i + (1<<(log-1)))]);
            else
                rmq[k][log][i] = max(rmq[k][log-1][i], rmq[k][log-1][min(n-1, i + (1<<(log-1)))]);
                
        }
    }
}
// l e r inclusives
int get_rmq(int k, int l, int r) {
    int len = r - l + 1;
    int bit = 31 - __builtin_clz(len);
    if (k == 0)
        return min(rmq[k][bit][l], rmq[k][bit][r - (1<<bit) + 1]);
    else
        return max(rmq[k][bit][l], rmq[k][bit][r - (1<<bit) + 1]);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &v[1][i]);
    for (int i = 0; i < n; i++) scanf("%d", &v[0][i]);
    build_rmq(0); build_rmq(1);

    lint ans = 0;
    for (int i = 0; i < n; i++) {
        int l1 = i, r1 = n;
        while (l1 < r1) {
            int mid = (l1 + r1) / 2;
            if (get_rmq(0, i, mid) < get_rmq(1, i, mid)) r1 = mid;
            else l1 = mid + 1;
        }
        int l2 = i, r2 = n;
        while (l2 < r2) {
            int mid = (l2 + r2) / 2;
            if (get_rmq(0, i, mid) <= get_rmq(1, i, mid)) r2 = mid;
            else l2 = mid + 1;
        }
        if (l2 < n && get_rmq(0, i, l2) == get_rmq(1, i, l2)) {
            // printf("i = %d: from %d to %d\n", i, l2, l1 - 1);
            ans += l1 - l2;
        }
    }
    cout << ans << endl;    
    return 0;
}
