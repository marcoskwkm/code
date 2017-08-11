#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXZ = 3800, MAXK = 210;

int dp[MAXK][MAXZ];

int main() {
    int n, k;
    cin >> n >> k;
    vector<pii> v;
    for (int i = 0; i < n; i++) {
        lint x;
        cin >> x;
        int n2 = 0, n5 = 0;
        while (x % 2 == 0) {
            n2++;
            x /= 2;
        }
        while (x % 5 == 0) {
            n5++;
            x /= 5;
        }
        v.push_back(pii(n2, n5));
    }
    for (int i = 0; i <= k; i++)
        for (int j = 0; j < MAXZ; j++)
            dp[i][j] = -INF;
    dp[0][0] = 0;
    int ans = 0;
    for (pii p: v) {
        for (int q = k; q > 0; q--) {
            for (int i = MAXZ - 1; i >= p.first; i--) {
                dp[q][i] = max(dp[q][i], dp[q - 1][i - p.first] + p.second);
                ans = max(ans, min(dp[q][i], i));
            }
        }                    
    }
    cout << ans << endl;
    return 0;
}
