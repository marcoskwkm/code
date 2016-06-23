#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int v[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    sort(v, v + n);
    int ans = 1;
    for (int i = 0; i < n; i++)
        if (v[i] >= ans)
            ans++;
    printf("%d\n", ans);
    return 0;
}
