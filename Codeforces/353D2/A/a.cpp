#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    bool ok = 0;
    if (c < 0)
        if ((a % c + c) % c == (b % c + c) % c && a >= b)
            ok = 1;
    if (c == 0)
        if (a == b)
            ok = 1;
    if (c > 0)
        if ((a % c + c) % c == (b % c + c) % c && a <= b)
            ok = 1;
    printf("%s\n", ok ? "YES" : "NO");
    return 0;
}
