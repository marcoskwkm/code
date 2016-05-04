#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<int, lint> pil;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 20;

lint w[MAXN], c[MAXN];
int idx[MAXN];
lint ans;
int n, m;

void go(int i, lint cur_w, lint cur_c) {
    lint upper_w = cur_w, upper_c = cur_c;
//    if (i == n) debug("reached leaf (%lld vs %lld)\n", cur_c, ans);
    for (int j = i; j <= n; j++) {
        if (j == n) {
            if (upper_c > ans) debug("ans = %lld\n", ans);
            ans = max(ans, upper_c);
            return;
        }
        int id = idx[j];
        if (upper_w + id*w[id] <= m) {
            upper_w += id*w[id];
            upper_c += id*c[id];
            if (upper_c > ans) debug("ans = %lld\n", ans);
            ans = max(ans, upper_c);
        }
        else {
            int left = m - upper_w;
            debug("upper_c = %lld, ans = %lld\n", upper_c, ans);
            debug("left = %d, c = %lld, w = %lld\n", left, c[id], w[id]);
            if (c[id]*left <= (ans - upper_c)*w[id]) {
                debug("pruned\n");
                return;
            }
            break;
        }
    }
    int id = idx[i];
    for (int j = id; j >= 0; j--) {
        if (cur_w + j*w[id] > m) continue;
        go(i + 1, cur_w + j*w[id], cur_c + j*c[id]);
    }
}            

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &w[i]);
            idx[i - 1] = i;
        }
        for (int i = 1; i <= n; i++)
            scanf("%lld", &c[i]);
        sort(idx, idx + n, [](int a, int b) {
            return c[a]*w[b] > c[b]*w[a];
        });
        ans = 0;
        go(0, 0, 0);
        printf("%lld\n", ans);
    }    
    return 0;
}
