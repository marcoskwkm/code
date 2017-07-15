#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

int main() {
    int n;
    cin >> n;
    int c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%*d%d", &k);
        if (k == 1) c1++;
        else c2++;
    }
    if (c1 > c2) swap(c1, c2);
    if (11 * c1 < c2) printf("-1\n");
    else printf("%d\n", (c1 + c2 + 11) / 12);    
    return 0;
}
