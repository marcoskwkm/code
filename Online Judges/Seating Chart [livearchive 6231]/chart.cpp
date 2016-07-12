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

void update(int i) {
    for (; i < MAXN; i += i & -i)
        bit[i]++;
}

int query(int i) {
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret += bit[i];
    return ret;
}

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        map<string, int> mp;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            mp[s] = i + 1;
        }
        lint ans = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            ans += i - query(mp[s]);
            update(mp[s]);
        }
        printf("%lld\n", ans);
        memset(bit, 0, sizeof(bit));
    }        
    return 0;
}
