#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

int v1[MAXN], v2[MAXN];
int idx[MAXN];
int n;

lint solve() {
    multiset<pll> increase;
    vector<pll> rest;    
    for (int i = 0; i < n; i++) {
        if (v1[i] <= v2[i])
            increase.insert(pll(v1[i], v2[i] - v1[i]));
        else
            rest.push_back(pll(v2[i], v1[i]));
    }
    lint space = 0, extra = 0;
    while (!increase.empty()) {
        if (increase.begin()->first > space) {
            lint add = increase.begin()->first - space;
            extra += add;
            space += add;
        }
        space += increase.begin()->second;
        increase.erase(increase.begin());
    }
    sort(rest.begin(), rest.end(), greater<pll>());
    for (pll p: rest) {
        if (p.second > space) {
            lint add = p.second - space;
            extra += add;
            space += add;
        }
        space += p.first - p.second;
    }
    return extra;    
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &v1[i], &v2[i]);
    printf("%lld\n", solve());
    return 0;
}
