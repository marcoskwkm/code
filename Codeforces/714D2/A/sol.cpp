#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readIntArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%d", &x); })
#define readLintArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%lld", &x); })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, k;
        cin >> n >> k;
        if (k > (n - 1) / 2) {
            printf("-1\n");
            continue;
        }
        vector<int> v(n, -1);
        for (int i = 0; i < k; i++) {
            v[2 * i + 1] = n - i;
        }
        int cur = 1;
        for_each(v.begin(), v.end(), [&](int &x) {
            if (x == -1) {
                x = cur++;
            }
            printf("%d ", x);
        });
        printf("\n");
    }
    return 0;
}
