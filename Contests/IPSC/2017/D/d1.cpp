#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

vector<int> gen_all() {
    vector<int> ret;
    for (int i = 1; i <= 9; i++) {
        ret.push_back(i);
        for (int j = 0; j <= 9; j++) {
            if (i == j) continue;
            ret.push_back(10*i + j);
            for (int k = 0; k <= 9; k++) {
                if (k == i || k == j) continue;
                ret.push_back(100*i + 10*j + k);
                for (int l = 0; l <= 9; l++) {
                    if (l == i || l == j || l == k) continue;
                    ret.push_back(1000*i + 100*j + 10*k + l);
                }
            }
        }
    }
    return ret;
}

const int MAXN = 10010;
int dp[MAXN];
int last[MAXN];

int main() {
    int t;
    vector<int> all = gen_all();
    debug("Found %d numbers\n", (int)all.size());
    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for (int x: all) {
        for (int i = MAXN; i >= x; i--) {
            if (1 + dp[i - x] < dp[i]) {
                dp[i] = 1 + dp[i - x];
                last[i] = x;
            }
        }
    }
    
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        printf("%d", dp[n]);
        while (n) {
            printf(" %d", last[n]);
            n -= last[n];
        }
        printf("\n");
    }        
    return 0;
}
