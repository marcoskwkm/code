#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 5010;

int q[MAXN];
int v[MAXN];
int ans[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]);
    for (int l = 0; l < n; l++) {
        memset(q, 0, sizeof(q));
        int hi = -1, c = INF;
        for (int r = l; r < n; r++) {
            q[v[r]]++;
            if (q[v[r]] > hi) {
                hi = q[v[r]];
                c = v[r];
            }
            else if (q[v[r]] == hi) {
                if (v[r] < c) {
                    c = v[r];
                }
            }
            ans[c]++;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
