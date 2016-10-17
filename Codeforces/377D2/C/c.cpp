#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    lint x[3];
    cin >> x[0] >> x[1] >> x[2];
    lint nd = max(x[0], max(x[1], x[2]));
    lint ans = LINF;
    for (int s = 0; s < 2; s++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                lint got = 0;
                for (int k = 0; k < 3; k++) {
                    lint needs = nd - 2;
                    if (k >= i) needs++;
                    if (k <= j) needs++;
                    if (needs < x[k]) {
                        got = LINF;
                        break;
                    }
                    got += needs - x[k];
                }
                ans = min(ans, got);
            }
        }
        nd++;
    }
    cout << ans << endl;    
    return 0;
}
