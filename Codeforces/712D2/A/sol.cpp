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
const int MAXN = (int)3e5 + 10;

char s[MAXN];
char ans[MAXN];

int main() {
    int t;
    for (cin >> t; t--;) {
        scanf(" %s", s);
        int len = strlen(s);
        if (all_of(s, s + len, [](char c) { return c == 'a'; })) {
            printf("NO\n");
            continue;
        }

        ans[len + 1] = 0;
        int vl = 0, vr = len;
        int l = 0, r = len - 1;
        bool flag = 0;
        while (l <= r) {
            if (!flag) {
                if (s[l] != 'a') {
                    flag = 1;
                    ans[vl++] = s[l++];
                    ans[vr--] = 'a';
                } else if (s[r] != 'a') {
                    flag = 1;
                    ans[vr--] = s[r--];
                    ans[vl++] = 'a';
                } else {
                    ans[vl++] = s[l++];
                    ans[vr--] = s[r--];
                }
            } else {
                ans[vl++] = s[l++];
                ans[vr--] = s[r--];
            }
        }
        printf("YES\n");
        printf("%s\n", ans);
    }
    return 0;
}
