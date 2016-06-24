#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    int ans = 0;
    while (a != b) {
        if (a < b) swap(a, b);
        int m = b + 1;
        int q = a / m;
        ans += q * m;
        a -= q * m;
    }
    printf("%d\n", ans);
    return 0;
}
