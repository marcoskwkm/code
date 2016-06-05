#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        lint a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        lint area = a*b;
        lint sq = c*c;
        if (area % sq < sq - area%sq && area >= sq) {
            printf("%lld\n", area - area%sq);
        }
        else {
            printf("%lld\n", area - area%sq + sq);
        }        
    }        
    return 0;
}
