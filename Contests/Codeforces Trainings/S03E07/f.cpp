#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

lint v[MAXN];

int main() {
    int n;
    lint target, s = 0;
    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &v[i]);
        s += v[i];
    }

    lint ans = LINF;
    lint cur_h = 0, sv = 0;
    for (int i = 0; i < n; i++) {
        if (cur_h >= target) {
            ans = min<lint>(ans, i);
            break;
        }
        lint l = 0, r = (2e9 + 10) / n;
        while (l < r) {
            lint k = (l + r) / 2;
            lint h = (k * n + i) * (k * n + i + 1) / 2 + k * s + sv;
            if (h >= target) r = k;
            else l = k + 1;
        }
        ans = min(ans, l * n + i);
        cur_h += v[i] + i + 1;
        sv += v[i];
    }

    cout << ans << endl;    
    return 0;
}
