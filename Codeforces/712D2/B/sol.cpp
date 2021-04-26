#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readIntArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%d", &x); })
#define readLintArray(v, n) for_each(v.begin(), v.begin() + n, [](lint &x) { scanf("%lld", &x); })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        vector<int> v1(n), v2(n);
        for_each(v1.begin(), v1.end(), [](int &x) {
            char c;
            scanf(" %c", &c);
            x = (c == '1' ? 1 : 0);
        });
        for_each(v2.begin(), v2.end(), [](int &x) {
            char c;
            scanf(" %c", &c);
            x = (c == '1' ? 1 : 0);
        });

        vector<int> q(n);
        for (int i = 0; i < n; i++) {
            q[i] = (i > 0 ? q[i - 1] : 0) + v1[i];
        }

        bool flag = 1;
        int flip = 0;
        for (int i = n - 1; i >= 0; i--) {
            if ((v1[i] ^ flip) == v2[i]) {
                continue;
            }
            if (2 * q[i] != i + 1) {
                flag = 0;
                break;
            }
            flip ^= 1;
        }

        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}
