
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int good[] = {1, 2, 3, 3, 4, 10};
const int evil[] = {1, 2, 2, 2, 3, 5, 10};

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        lint sgood = 0, sevil = 0;
        for (int i = 0; i < 6; i++) {
            lint cnt;
            scanf("%lld", &cnt);
            sgood += cnt * good[i];
        }
        for (int i = 0; i < 7; i++) {
            lint cnt;
            scanf("%lld", &cnt);
            sevil += cnt * evil[i];
        }
        printf("Battle %d: ", t);
        if (sgood > sevil) printf("Good triumphs over Evil\n");
        else if (sgood == sevil) printf("No victor on this battle field\n");
        else printf("Evil eradicates all trace of Good\n");
    }            
    return 0;
}
