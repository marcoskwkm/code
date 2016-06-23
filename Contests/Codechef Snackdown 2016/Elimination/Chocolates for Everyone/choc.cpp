#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        lint n, c;
        scanf("%lld%lld", &n, &c);
        if (n == 1) {
            printf("Yes\n");
            continue;
        }
        if (2*c % n) {
            printf("No\n");
            continue;
        }
        lint m = 2*c / n;
        if (m % 2 == 1 && (n - 1) % 2 == 0) {
            printf("No\n");
            continue;
        }
        if (m % 2 == (n - 1) % 2) {
            if (m - 2 >= n - 1) printf("Yes\n");
            else printf("No\n");
        }
        else {
            if (m - 2 >= 2 * (n - 1)) printf("Yes\n");
            else printf("No\n");
        }
    }        
    return 0;
}
