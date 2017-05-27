#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
    
int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int c1, r1, c2, r2;
        scanf("%d%d%d%d", &c1, &r1, &c2, &r2);
        if (x1 == x2 && y1 == y2) {
            swap(x1, c1);
            swap(x2, c2);
            swap(y1, r1);
            swap(y2, r2);
        }
        if (x1 == x2) {
            swap(x1, y1);
            swap(x2, y2);
            swap(c1, r1);
            swap(c2, r2);
        }
        // y1 == y2
        bool ans = 0;
        if (r1 == r2) {
            if (x1 > x2) swap(x1, x2);
            if (c1 > c2) swap(c1, c2);
            ans = (r1 == y1) && (min(x2, c2) >= max(x1, c1));
        }
        else {
            // c1 == c2
            ans = (c1 == x1 || c1 == x2) && (r1 == y1 || r2 == y1);
        }
        printf("%s\n", ans ? "yes" : "no");
    }        
    return 0;
}
