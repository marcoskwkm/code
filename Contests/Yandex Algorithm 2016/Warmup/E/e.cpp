#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef unsigned long long ulint;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    ulint x = 0, x1 = 0;
    ulint a1;
    for (int i = 0; i <= n; i++) {
        ulint a;
        scanf("%llu", &a);
        if (i) x ^= a;
        if (i & 1) x1 ^= a;
        if (i == 1) a1 = (a & 1);
    }
    if ((x & 1) == 0) {
        printf("Yes\n");
    }
    else {
        if (m == 1) {
            printf("No\n");
        }
        else {
            if (a1 && (x1 & 1)) {
                printf("No\n");
            }
            else printf("Yes\n");
        }
    }        
    return 0;
}
