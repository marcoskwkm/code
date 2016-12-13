#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int modexp(int b, int e, int m) {
    b %= m;
    int ret = 1;
    while (e) {
        if (e & 1) ret = ret * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return ret;
}


int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", modexp(a, b, 10));
    }
    return 0;
}
