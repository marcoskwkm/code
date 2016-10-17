#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

int ans[MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int last = k;
    int total = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        int add = max(0, k - last - x);
        ans[i] = x + add;
        last = x + add;
        total += add;
    }
    printf("%d\n", total);
    for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i + 1 == n ? '\n' : ' ');    
    return 0;
}
