#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int cost[MAXN];
int idx[MAXN][2];
string s[MAXN][2];
int n;

lint dp[MAXN][2];

lint go(int i, int k) {
    if (i == n - 1) return 0;
    if (dp[i][k] != -1) return dp[i][k];
    lint ret = LINF;
    if (idx[i][k] <= idx[i + 1][0]) ret = min(ret, go(i + 1, 0));
    if (idx[i][k] <= idx[i + 1][1]) ret = min(ret, go(i + 1, 1) + cost[i + 1]);
    return dp[i][k] = ret;
}
    
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &cost[i]);
    set<string> cj;
    for (int i = 0; i < n; i++) {
        cin >> s[i][0];
        s[i][1] = s[i][0];
        reverse(s[i][1].begin(), s[i][1].end());
        cj.insert(s[i][0]);
        cj.insert(s[i][1]);
    }

    map<string, int> mp;
    int cnt = 0;
    for (auto str: cj)
        mp[str] = cnt++;

    for (int i = 0; i < n; i++) {
        idx[i][0] = mp[s[i][0]];
        idx[i][1] = mp[s[i][1]];
    }

    memset(dp, -1, sizeof(dp));
    lint ans0 = go(0, 0), ans1 = go(0, 1) + cost[0];
    lint ans = min(ans0, ans1);

    cout << (ans == LINF ? -1 : ans) << endl;        
    return 0;
}
