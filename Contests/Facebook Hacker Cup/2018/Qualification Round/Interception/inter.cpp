#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i <= n; i++) scanf("%*d");
        if (n == 1) printf("Case #%d: 1\n0\n", t);
        else printf("Case #%d: 0\n", t);
    }
    return 0;
}
