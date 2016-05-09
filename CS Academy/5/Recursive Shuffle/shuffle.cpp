#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int get(int x, int k) {
    int ret = 0;
    for (int i = 0; i <= k; i++) {
        ret = 2*ret + (x & 1);
        x /= 2;
    }
    return ret;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int kk = 0, nn = n;
    while (nn) {
        kk++;
        nn /= 2;
    }
    int ok = 1;
    int x;
    scanf("%d", &x);
    int last = get(x - 1, kk) - 1;
    for (int i = 1; i < m; i++) {
        int nxt;
        scanf("%d", &nxt);
        int inxt = get(nxt - 1, kk);
        if (inxt > last) {
            ok = 0;
            break;
        }
        while (last > inxt) {
            int xx = get(last, kk);
            if (0 <= xx && xx <= n - 1) {
                ok = 0;
                break;
            }
            last--;
        }
        last = inxt - 1;
    }
    printf("%d\n", ok);    
    return 0;
}
