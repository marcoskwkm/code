#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAXF = 110;
int grundy[MAXF];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        lint x = 0;
        for (scanf("%d", &n); n--;) {
            lint p;
            scanf("%lld",  &p);
            if (p <= 1) {
                x ^= p;
                continue;
            }
            lint pow2 = 1;
            while (2*pow2 + 1 <= p) pow2 *= 2;
            lint nim = 2 * pow2;
            x ^= nim + p - (pow2 + 1);
            printf("nim[%lld] = %lld\n", p, nim + p - (pow2 + 1));
        }
        printf("%c\n", x ? 'A' : 'B');
    }        
    return 0;
}
