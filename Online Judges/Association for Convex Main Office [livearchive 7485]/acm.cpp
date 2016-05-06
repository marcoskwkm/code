#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 10000, MAXD = 1000;
const int MAXL = 1010;

int dp[MAXN];
pii used[MAXL][MAXN];

int main() {
    vector<pii> delta;
    for (int dx = 1; dx < MAXD; dx++) {
        for (int dy = dx + 1; dy < MAXD; dy++) {
            if (__gcd(dx, dy) == 1) {
                delta.push_back(pii(dx, dy));
            }
        }
    }
    sort(delta.begin(), delta.end(), [](pii a, pii b) {
        return a.second + a.first < b.first + b.second;
    });

    int got = 0;
    lint sum = 0;
    vector<pii> ans;
    while (got < 50000 && sum <= (int)2e7) {        
        sum += delta[got].first + delta[got].second;
        ans.push_back(delta[got]);
        got++;
    }
    sort(ans.begin(), ans.end(), [](pii a, pii b) {
        return a.second*b.first > a.first*b.second;
    });

    for (int i = (int)ans.size() - 1; i >= 0; i--)
        ans.push_back(pii(ans[i].second, ans[i].first));
    for (int i = (int)ans.size() - 1; i >= 0; i--)
        ans.push_back(pii(ans[i].first, -ans[i].second));
    for (int i = (int)ans.size() - 1; i >= 0; i--)
        ans.push_back(pii(-ans[i].first, ans[i].second));

    int cx = 0, cy = (int)2e7;
    vector<pii> poly;
    poly.push_back(pii(cx, cy));
    for (pii p: ans) {
        cx += p.first;
        cy += p.second;
        poly.push_back(pii(cx, cy));
    }
    poly.pop_back();

    int n;
    while (scanf("%d", &n) > 0) {
        for (int i = 0; i < n; i++)
            printf("%d %d\n", poly[i].first, poly[i].second);
    }    
    return 0;
}
