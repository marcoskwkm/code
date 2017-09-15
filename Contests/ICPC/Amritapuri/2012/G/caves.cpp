#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 60;

int q[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            int cnt = 0;
            for (char c: s) cnt += (c == '*');
            q[i] = cnt;
            ans += cnt;
        }
        sort(q, q + n, [=](int a, int b) { return m - 2*a > m - 2*b; });
        
        for (int i = 0; i < n && q[i] < m - q[i] && k; i++, k--) {
            ans += m - 2*q[i];
            q[i] = m - q[i];
        }

        if (k & 1) {
            sort(q, q + n, [=](int a, int b) { return m - 2*a > m - 2*b; });
            ans += m - 2*q[0];
        }
        printf("%d\n", ans);
    }        
    return 0;
}
