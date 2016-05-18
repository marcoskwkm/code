#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int LOG = 20;

int r[MAXN];
lint bit[MAXN];
int n;

void bit_update(int i, lint val) {
    for (; i <= n; i += i & -i)
        bit[i] = min(bit[i], val);
}

lint bit_query(int i) {
    lint ret = LINF;
    for (; i; i -= i & -i)
        ret = min(ret, bit[i]);
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d", &r[i]);

    memset(bit, INF, sizeof(bit));
    bit_update(n, 0);
    lint ans = 0;
    for (int i = n - 1; i > 0; i--) {
        lint got = bit_query(r[i]) + n - r[i] + n - i;
        bit_update(i, got - (n - i));
        ans += got;
    }
        
    cout << ans << endl;    
    return 0;
}
