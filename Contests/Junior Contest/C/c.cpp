#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int bit[MAXN];

void update(int i, int val) {
    i++;
    for (; i < MAXN; i += i&-i)
        bit[i] = max(bit[i], val);
}

int query(int i) {
    i++;
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret = max(ret, bit[i]);
    return ret;
}

int main() {
    int n;
    while (scanf("%d", &n) > 0 && n) {
        memset(bit, 0, sizeof(bit));
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            mp[x] = i;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            if (mp.find(x) == mp.end()) continue;
            int got = query(mp[x]) + 1;
            ans = max(ans, got);
            update(mp[x], got);
        }
        printf("%d\n", ans);
    }        
    return 0;
}
