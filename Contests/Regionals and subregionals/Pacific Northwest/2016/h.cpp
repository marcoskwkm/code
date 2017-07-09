#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)4e5 + 10;

lint bit[MAXN];

void update(int i, lint v) {
    for (; i < MAXN; i += i & -i)
        bit[i] = max(bit[i], v);
}

lint query(int i) {
    lint ret = 0;
    for (; i > 0; i -= i & -i)
        ret = max(ret, bit[i]);
    return ret;
}

int main() {
    lint n;
    int k;
    scanf("%lld%d", &n, &k);
    vector<pll> v;
    vector<lint> x;
    map<lint, int> mp;
    for (int i = 0; i < k; i++) {
        lint l, r;
        scanf("%lld%lld", &l, &r);
        v.push_back(pll(l, r));
        x.push_back(l);
        x.push_back(r);
    }
    sort(v.begin(), v.end(), [](pll a, pll b) { return a.second < b.second; });
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    for (int i = 1; i < (int)x.size(); i++)
        mp[x[i]] = i;
    
    lint ans = 0;
    for (const pll &p: v) {
        lint got = query(mp[p.first] - 1) + p.second - p.first + 1;
        if (got > query(mp[p.second])) update(mp[p.second], got);
        ans = max(ans, got);
    }

    printf("%lld\n", n - ans);        
    return 0;
}
