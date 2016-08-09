#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

int v[MAXN];
int nxt[MAXN];
bool active[MAXN];
lint acc[MAXN];

int main() {
    int n;
    lint m;
    scanf("%d%lld", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        acc[i] = v[i] + (i > 0 ? acc[i - 1] : 0);
    }
    
    stack<pii> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top().first < v[i]) st.pop();
        if (st.empty()) nxt[i] = n;
        else nxt[i] = st.top().second;
        st.push(pii(v[i], i));
    }
    int at = 0;
    while (at != n) {
        active[at] = 1;
        at = nxt[at];
    }
    active[n] = 1;

    deque<pii> fila;
    int r = 0;
    lint cur = 0;
    int hi = 0;
    while (r < n && max(0, hi - v[r]) + cur <= m) {
        while (!fila.empty() && fila.back().first < v[r]) fila.pop_back();
        fila.push_back(pii(v[r], r));
        cur += max(0, hi - v[r]);
        hi = max(hi, v[r]);
        r++;
    }
    // printf("l = 0: r = %d (used %lld)\n", r, cur);
        
    lint ans = r;
    for (int l = 1; l < n; l++) {
        active[l - 1] = 0;
        at = nxt[l];
        int last_at = l;
        // printf("cur = %lld\n", cur);
        if (v[l] <= v[l - 1]) {
            while (1) {
                cur -= max(0, min(r, at) - last_at) * lint(v[l - 1] - v[last_at]);
                if (active[at]) break;
                active[at] = 1;
                last_at = at;
                at = nxt[at];
            }
        }
        // printf("cur = %lld\n", cur);

        if (fila.front().second == l - 1) fila.pop_front();
        while (r < n && max(0, fila.front().first - v[r]) + cur <= m) {
            while (!fila.empty() && fila.back().first < v[r]) fila.pop_back();
            fila.push_back(pii(v[r], r));
            cur += max(0, fila.front().first - v[r]);
            r++;
        }
        ans += r - l;
        // printf("l = %d: r = %d (used %lld)\n", l, r, cur);
    }

    printf("%lld\n", ans);    
    return 0;
}
