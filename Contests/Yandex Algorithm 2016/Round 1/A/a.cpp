#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int p, a, b;
    scanf("%d%d%d", &p, &a, &b);
    int ans = max(p, a + b);
    if (p < b) printf("-1\n");
    else printf("%d\n", ans);
    return 0;
}
