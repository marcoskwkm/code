#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;
const int MAXND = MAXN*MAXN;
const int BLOCK = 35;

int l[MAXND], r[MAXND], val[MAXND];
int head[MAXN];
int cur;

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int r = 0; r < n; r++) {
        val[cur] = -1;
        l[cur] = -1;
        head[r] = cur++;
        for (int c = 0; c < m; c++) {
            scanf("%d", &val[cur]);
            l[cur] = cur - 1;
            r[cur - 1] = cur;
            cur++;
        }
        r[cur - 1] = -1;
    }
        
    
    return 0;
}
