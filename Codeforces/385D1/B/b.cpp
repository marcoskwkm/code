#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010, LOG = 12;

int low[LOG][2][MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 10; i++) {
        vector<int> ask[2];
        for (int j = 1; j <= n; j++) {
            if (j & (1 << i))
                ask[1].push_back(j);
            else
                ask[0].push_back(j);
        }
        for (int bit = 0; bit < 2; bit++) {
            if (ask[bit].size() == 0) {
                for (int j = 1; j <= n; j++)
                    low[i][bit][j] = INF;
                continue;
            }
            printf("%d\n", (int)ask[bit].size());
            for (int x: ask[bit]) printf("%d ", x);
            printf("\n");
            fflush(stdout);
            for (int j = 1; j <= n; j++)
                scanf("%d", &low[i][bit][j]);
        }
    }

    printf("-1\n");
    for (int row = 1; row <= n; row++) {
        int ans = INF;
        for (int i = 9; i >= 0; i--) {
            if (row & (1 << i)) ans = min(ans, low[i][0][row]);
            else ans = min(ans, low[i][1][row]);
        }
        printf("%d ", ans);
    }
    printf("\n");
    fflush(stdout);    
    return 0;
}
