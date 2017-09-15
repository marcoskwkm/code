#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = (int)1e5 + 10;

int dp[MAXV];

int main() {
    int n;
    cin >> n;
    vector<int> p;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        p.push_back(x);
    }
    sort(p.begin(), p.end());
    for (int i = 0; i + 1 < n; i++)
        for (int v = p.back(); v >= p[i]; v--)
            dp[v] = max(dp[v], dp[v - p[i]] + 1);
    cout << dp[p.back()] + 1 << endl;    
    return 0;
}
