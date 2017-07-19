#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

lint bit[MAXN];

void update(int i, lint v) {
    for (; i < MAXN; i += i & -i)
        bit[i] = min(bit[i], v);
}

lint query(int i) {
    lint ret = LINF;
    for (; i > 0; i -= i & -i)
        ret = min(ret, bit[i]);
    return ret;
}

int main() {
    vector<pll> v;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        lint x;
        scanf("%lld", &x);
        v.push_back(pll(x, i));
    }
    sort(v.begin(), v.end(), greater<pll>());
    lint ans = LINF;
    memset(bit, LINF, sizeof(bit));
    for (pll p: v) {
        int i;
        lint val;
        tie(val, i) = p;
        ans = min(ans, query(i) - val);
        update(i, val);
    }
    cout << ans << endl;    
    return 0;
}
