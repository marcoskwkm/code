#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

lint dp[MAXN];
int n, k;
lint go(int i, const vector<pll> &v) {
    if (i == (int)v.size()) return 0;
    if (dp[i] != -1) return dp[i];
    lint n_trips = (v[i].second + k - 1) / k;
    lint cur = 2*n_trips*v[i].first;
    lint rem = k - v[i].second % k;
    if (rem == k) rem = 0;
    lint ret = cur + go(i + 1, v);
    for (int j = 1; i + j < (int)v.size(); j++) {
        if (rem >= v[i + j].second) {
            rem -= v[i + j].second;
            n_trips = 0;
        }
        else {
            n_trips = (v[i + j].second - rem + k - 1) / k;
            rem = k - (v[i + j].second - rem) % k;
            if (rem == k) rem = 0;
        }
        cur += 2*(v[i + j].first - v[i + j - 1].first + n_trips*v[i + j].first);
        ret = min(ret, cur + go(i + j + 1, v));
    }
    return dp[i] = ret;
}

int main() {
    scanf("%d%d", &n, &k);
    vector<pll> neg, pos;
    for (int i = 0; i < n; i++) {
        lint x, m;
        scanf("%lld%lld", &x, &m);
        if (x < 0) neg.push_back(pll(-x, m));
        else if(x > 0) pos.push_back(pll(x, m));
    }
    sort(neg.begin(), neg.end());
    sort(pos.begin(), pos.end());
    memset(dp, -1, sizeof(dp));
    lint ans = go(0, neg);
    memset(dp, -1, sizeof(dp));
    ans += go(0, pos);
    printf("%lld\n", ans);    
    return 0;
}
