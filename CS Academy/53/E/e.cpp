#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = (1 << 17);

int cnt[MAXV];
lint f[MAXV];
bool seen[MAXV];

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        f[v[i]]++;
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        if (seen[v[i]]) ans = max(ans, v[i]);
        else {
            seen[v[i]] = 1;
            int submask = v[i];
            while (submask >= 0) {
                if (f[submask] > 0) ans = max(ans, v[i]);
                cnt[submask] += f[v[i]];
                if (submask == 0) break;
                submask = (submask - 1) & v[i];
            }
            int rev = (~v[i]) & (MAXV - 1);
            int sub = rev;
            while (sub > 0) {
                if (cnt[sub] > 0) ans = max(ans, v[i] | sub);
                sub = (sub - 1) & rev;
            }
        }
    }
    lint ans2 = 0;
    lint add = 0;
    for (int mask = (ans - 1) & ans; mask >= 0; mask = (mask - 1) & ans) {
        // debug("mask = %d, f = %lld, cnt[%d] = %d\n", mask, f[mask], ans ^ mask, cnt[ans ^ mask]);
        ans2 += f[mask] * (cnt[ans ^ mask] - f[ans]);
        add += f[mask];
        if (mask == 0) break;
    }
    // debug("ans2 = %lld\n", ans2);
    ans2 = ans2 / 2 + f[ans] * (n - f[ans]) + (f[ans] * (f[ans] - 1)) / 2;

    printf("%d %lld\n", ans, ans2);    
    return 0;
}
