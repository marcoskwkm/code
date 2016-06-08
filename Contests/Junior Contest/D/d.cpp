#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

int v1[MAXN], v2[MAXN];

int main() {
    int n;
    while (scanf("%d", &n) > 0 && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", &v1[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &v2[i]);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int len = 0;
                while (i + len < n && j + len < n &&
                       v1[i + len] == v2[j + len]) len++;
                ans = max(ans, len);
            }
        }
        printf("%d\n", ans);
    }        
    return 0;
}
