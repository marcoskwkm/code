#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXW = 2010;

lint dp[MAXW];
vector<pii> candies[MAXW];
lint opt[MAXW][MAXW];

int main() {
    int t;
    for (cin >> t; t--;) {
        int m, n;
        cin >> m >> n;
        map<int, int> mp;
        for (int i = 0; i <= m; i++) candies[i].clear();
        for (int i = 0; i < n; i++) {
            int w, a, b;
            cin >> w >> a >> b;
            candies[w].push_back(pii(a, b));
        }
        memset(opt, 0, sizeof(opt));
        for (int w = 1; w <= m; w++) {
            if (candies[w].empty()) continue;
            sort(candies[w].begin(), candies[w].end(), [](pii a, pii b) {
                return a.first + a.second > b.first + b.second;
            });
            int max_a = 0;
            for (pii p: candies[w]) max_a = max(max_a, p.first);
            int last = 0;
            while (last + 1 < (int)candies[w].size() &&
                   candies[w][last + 1].first + candies[w][last + 1].second >= max_a) last++;
            for (int k = 1; k <= last + 1; k++)
                opt[w][k] = opt[w][k - 1] + candies[w][k - 1].first + candies[w][k - 1].second;
            for (int k = last + 2; k * w <= m; k++)
                opt[w][k] = opt[w][k - 1] + max_a;            
        }        
            
        fill(dp, dp + MAXW, -LINF);
        dp[0] = 0;
        for (int w = 1; w <= m; w++)
            for (int j = m; j >= w; j--)
                for (int k = 1; j >= k * w; k++)
                    dp[j] = max(dp[j], opt[w][k] + dp[j - k * w]);
        cout << accumulate(dp, dp + m + 1, 0, [](lint a, lint b) { return max(a, b); }) << endl;
    }        
    return 0;
}
