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
        scanf("%d", &n);
        vector<int> s1(n), s2(n);
        string s;
        cin >> s;
        int q0 = count(s.begin(), s.end(), '0');
        int q1 = n - q0;
        if (q0 % 2 == 1 || q1 % 2 == 1 || s[0] != '1' || s[n - 1] != '1') {
            printf("NO\n");
            continue;
        }

        printf("YES\n");
        int c0 = 0, c1 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                if (2 * c1 >= q1) {
                    s1[i] = s2[i] = 0;
                } else {
                    s1[i] = s2[i] = 1;
                }
                c1++;
            } else {
                if (c0 % 2 == 0) {
                    s1[i] = 1;
                    s2[i] = 0;
                } else {
                    s1[i] = 0;
                    s2[i] = 1;
                }
                c0++;
            }
        }

        for_each(s1.begin(), s1.end(), [](int x) { printf("%c", x ? '(' : ')'); });
        printf("\n");
        for_each(s2.begin(), s2.end(), [](int x) { printf("%c", x ? '(' : ')'); });
        printf("\n");
    }
    return 0;
}
