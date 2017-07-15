#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXQ = (int)1e5 + 10;

int ans[MAXQ];

int main() {
    vector<pll> event;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        lint x;
        scanf("%lld", &x);
        lint l = 0, r = INF;
        while (l < r) {
            lint mid = (l + r) / 2;
            if (10 * mid >= 9 * x) r = mid;
            else l = mid + 1;
        }
        lint ll = l;
        l = 0, r = INF;
        while (l < r) {
            lint mid = (l + r + 1) / 2;
            if (10 * mid <= 11 * x) l = mid;
            else r = mid - 1;
        }
        lint rr = l;
        event.push_back(pll(ll, 1));
        event.push_back(pll(rr + 1, -1));
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        lint q;
        cin >> q;
        event.push_back(pll(q, i + 2));
    }

    sort(event.begin(), event.end());

    int cnt = 0;
    for (pll p: event) {
        if (p.second == 1) cnt++;
        else if (p.second == -1) cnt--;
        else ans[p.second - 2] = cnt;
    }

    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);        
    return 0;
}
