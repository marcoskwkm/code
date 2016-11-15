#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    multiset<int> low;
    int acc = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (acc >= k) {
            acc -= k;
            low.insert(x);
        }
        else if (!low.empty() && *low.begin() < x) {
            ans += *low.begin();
            low.erase(low.begin());
            low.insert(x);
            acc++;
        }
        else {
            ans += x;
            acc++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
