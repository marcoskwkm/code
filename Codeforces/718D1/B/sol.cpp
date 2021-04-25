#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110, MAXM = 110;

multiset<int> s[MAXN];
multiset<pii> all;
int ans[MAXN][MAXM];

int main() {
    int t;
    for(scanf("%d", &t); t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int x;
                scanf("%d", &x);
                all.insert(pii(x, i));
                s[i].insert(x);
            }
        }
        int cur = 0;
        while (!all.empty()) {
            auto [x, k] = *all.begin();
            all.erase(all.begin());
            for (int i = 0; i < n; i++) {
                if (i == k) {
                    ans[i][cur] = x;
                    s[i].erase(s[i].find(x));
                } else {
                    ans[i][cur] = *s[i].rbegin();
                    all.erase(all.find(pii(*s[i].rbegin(), i)));
                    s[i].erase(s[i].find(*s[i].rbegin()));
                }
            }
            cur++;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", ans[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
