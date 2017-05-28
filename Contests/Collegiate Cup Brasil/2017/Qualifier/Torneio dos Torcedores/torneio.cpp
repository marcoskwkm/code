#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int h[5], t[5];

int main() {
    for (int i = 1; i <= 4; i++)
        scanf("%d%d", &h[i], &t[i]);

    int i1, h1 = 0, t1 = 0, i2, h2 = 0, t2 = 0;

    if (h[1] + t[1] >= h[2] + t[2]) {
        i1 = 1;
        h1 = h[1];
        t1 += t[1];
        t2 += t[2];
    }
    else {
        i1 = 2;
        h1 = h[2];
        t1 += t[2];
        t2 += t[1];
    }
    if (h[3] + t[3] >= h[4] + t[4]) {
        i2 = 3;
        h2 = h[3];
        t2 += t[3];
        t1 += t[4];
    }
    else {
        i2 = 4;
        h2 = h[4];
        t2 += t[4];
        t1 += t[3];
    }
    printf("%d\n", (h1 + t1 >= h2 + t2) ? i1 : i2);        
    return 0;
}
