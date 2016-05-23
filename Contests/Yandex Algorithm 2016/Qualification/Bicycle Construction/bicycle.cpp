#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 4010, MAXV = (int)1e6 + 10;

lint v[MAXN];
lint cnt[MAXV];

int main() {
    int n;
    vector<pll> vp;
    unordered_map<lint, lint> total;
    scanf("%d", &n);
    set<int> cj;
    for (int i = 0; i < n ; i++) {
        scanf("%lld", &v[i]);
        cnt[v[i]]++;
        cj.insert(v[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i] < v[j] || (v[i] == v[j] && i < j)) {
                vp.push_back(pll(v[i], v[j]));
                total[v[i] * v[j]]++;
            }
        }
    }
    sort(vp.begin(), vp.end());
    lint ans = 0;

    // a*b = c*d or a*a = b*c
    for (int i = 0; i < (int)vp.size();) {
        int j = i;
        while (j + 1 < (int)vp.size() && vp[i] == vp[j + 1]) j++;
        lint prod = vp[i].first * vp[i].second;
        lint q = j - i + 1;
        ans += q * (total[prod] - q);
        i = j + 1;
    }
    ans /= 2;
    
    // a*c = a*c
    for (int x: cj) {
        for (int y: cj) {
            if (x <= y) continue;
            ans += cnt[x] * (cnt[x] - 1) * cnt[y] * (cnt[y] - 1) / 4;
        }
    }
    
    // a*a = a*a
    for (int x: cj) {
        if (cnt[x] >= 4) {
            ans += cnt[x] * (cnt[x] - 1) * (cnt[x] - 2) * (cnt[x] - 3) / 4 / 3 / 2;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
