#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int w1[MAXN], w2[MAXN], h1[MAXN], h2[MAXN];

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        scanf("%d", &n);
        int low = INF, hiw = 0, loh = INF, hih = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &w1[i], &w2[i], &h1[i], &h2[i]);
            low = min(low, w1[i]);
            hiw = max(hiw, w2[i]);
            loh = min(loh, h1[i]);
            hih = max(hih, h2[i]);
        }
        bool ok = 0;
        for (int i = 0; i < n; i++) {
            if (w1[i] <= low && hiw <= w2[i] &&
                h1[i] <= loh && hih <= h2[i]) {
                ok = 1;
                break;
            }
        }
        printf("%s\n", ok ? "ANO" : "NIE");
    }            
    return 0;
}
