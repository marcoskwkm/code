#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int LOG = 20;

lint v[MAXN];
int nxt[LOG][MAXN];

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &v[i]);
    stack<pll> st;
    st.push(pii(0, n + 1));
    for (int i = n; i >= 1; i--) {
        while (st.top().first >= v[i]) st.pop();
        nxt[0][i] = st.top().second;
        st.push(pll(v[i], i));
    }
    nxt[0][n + 1] = n + 1;
    for (int e = 1; e < LOG; e++)
        for (int i = 1; i <= n + 1; i++)
            nxt[e][i] = nxt[e - 1][nxt[e - 1][i]];

    while (q--) {
        lint x, l, r;
        scanf("%lld%lld%lld", &x, &l, &r);
        while (l <= r) {
            x %= v[l];
            for (int i = LOG - 1; i >= 0; i--)
                if (v[nxt[i][l]] > x) l = nxt[i][l];
            l = nxt[0][l];
        }
        printf("%lld\n", x);
    }        
    return 0;
}
