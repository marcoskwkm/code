#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    lint n;
    while (scanf("%lld", &n) > 0) {
        bool foi[10];
        memset(foi, 0, sizeof(foi));
        int cnt = 0, k;
        for (k = 1; cnt < 10; k++) {
            lint m = k * n;
            while (m) {
                int d = m % 10;
                if (!foi[d]) {
                    foi[d] = 1;
                    cnt++;
                }
                m /= 10;
            }
        }
        printf("%d\n", k - 1);
    }            
    return 0;
}
