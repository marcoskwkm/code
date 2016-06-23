#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    lint ans = 0;
    for (int i = 1; i <= 5; i++) {
        if (i > n) break;
        for (int j = 1; j <= 5; j++) {
            if (j > m) break;
            if ((i + j) % 5) continue;
            lint q1 = (n - i) / 5 + 1, q2 = (m - j) / 5 + 1;
            ans += q1 * q2;
        }
    }
    cout << ans << endl;
    return 0;
}
