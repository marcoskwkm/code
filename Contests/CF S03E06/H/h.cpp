#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int LOG = 32;

int up[MAXN], down[MAXN];
int go[LOG][MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &up[i], &down[i]);
        mp[up[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        go[0][i] = mp[down[i]];
    for (int l = 1; l < LOG; l++)
        for (int i = 1; i <= n; i++)
            go[l][i] = go[l - 1][go[l - 1][i]];

    for (int i = 0; i < k; i++) {
        int x, t;
        scanf("%d%d", &x, &t);
        for (int j = 30; j >= 0; j--)
            if (t & (1 << j))
                x = go[j][x];
        printf("%d\n", x);
    }    
    return 0;
}
