/*
ID: marcosk1
LANG: C++11
PROB: rockers
*/

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 22;

int v[MAXN];
int n, t, m;
int dp[MAXN][MAXN][MAXN];

int go(int song, int disk, int length) {
    if (song == n || disk == m) return 0;
    if (dp[song][disk][length] != -1)
        return dp[song][disk][length];
    int ret = go(song + 1, disk, length);
    if (length + v[song] <= t)
        ret = max(ret, 1 + go(song + 1, disk, length + v[song]));
    else
        ret = max(ret, go(song, disk + 1, 0));
    return dp[song][disk][length] = ret;
}

int main() {
    #ifndef HOME
    freopen("rockers.in", "r", stdin);
    freopen("rockers.out", "w", stdout);
    #endif
    
    scanf("%d%d%d", &n, &t, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    memset(dp, -1, sizeof(dp));
    printf("%d\n", go(0, 0, 0));    
    return 0;
}
