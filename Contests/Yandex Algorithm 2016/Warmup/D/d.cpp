#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int x[5], y[5];
int p[] = {0, 1, 2, 3, 4};

bool check() {
    for (int i = 0; i < 5; i++) {
        int a = p[i], b = p[(i + 1)%5], c = p[(i + 2)%5], d = p[(i + 3)%5];
        int xr = x[a] - x[b], yr = y[a] - y[b];
        int xs = x[c] - x[b], ys = y[c] - y[b];
        if (xr*ys - yr*xs <= 0) return 0;
        int xt = x[d] - x[c], yt = y[d] - y[c];
        if (xr*yt - yr*xt <= 0) return 0;
    }
    return 1;
}

int main() {
    for (int i = 0; i < 5; i++)
        scanf("%d%d", &x[i], &y[i]);
    do {
        if (check()) {
            // printf("%d %d %d %d %d\n", p[0], p[1], p[2], p[3], p[4]);
            printf("Yes\n");
            return 0;
        }
    } while(next_permutation(p, p + 5));
        
    printf("No\n");
    return 0;
}
