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
    for (cin >> t; t--;) {
        lint n;
        cin >> n;
        if (n % 2050) {
            printf("-1\n");
            continue;
        }

        lint q = n / 2050;
        int ans = 0;
        while (q) {
            ans += q % 10;
            q /= 10;
        }
        printf("%d\n", ans);
    }
    return 0;
}
