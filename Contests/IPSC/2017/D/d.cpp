#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAXN = 10010;

bool foi[10];
bool check(int n) {
    memset(foi, 0, sizeof(foi));
    while (n) {
        if (foi[n % 10]) return 0;
        foi[n % 10] = 1;
        n /= 10;
    }
    return 1;
}    

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        debug("%d...\n", t);
        int n;
        scanf("%d", &n);
        if (check(n)) printf("1 %d\n", n);
        else {
            for (int x = (n + 1) / 2; x <= n; x++) {
                if (check(x) && check(n - x)) {
                    printf("2 %d %d\n", x, n - x);
                    break;
                }
            }
        }        
    }        
    return 0;
}
