#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int LOG = 20;

template<class C_TYPE> struct ConvexHullOpt {
    struct Line {
        C_TYPE a, b; // a + bx
        double end_l;
        int jmp[LOG];
        C_TYPE get(C_TYPE x) { return a + b*x; }
        Line(){}
        Line(C_TYPE aa, C_TYPE bb) { a = aa; b = bb; end_l = -LINF; }
    };

    vector<Line> deq;

    double cross(const Line &r, const Line &s) {
        return double(s.a - r.a) / (r.b - s.b);
    }

    bool add_line(C_TYPE a, C_TYPE b) {
        if (!deq.empty() && deq.back().b == b && deq.back().a <= a) return 0;
        Line newline(a, b);
        int i = deq.size() - 1;
        while (i >= 0 && cross(newline, deq[i]) < deq[i].end_l) {
            i = deq[i].jmp[0];
        }
        if (i >= 0) newline.end_l = cross(newline, deq[i]);
        newline.jmp[0] = i;
        for (int j = 1; j < LOG; j++) {
            int tmp = newline.jmp[j - 1];            
            newline.jmp[j] = (tmp == -1 ? -1 : deq[tmp].jmp[j - 1]);
        }            
        deq.push_back(newline);
        return 1;
    }

    C_TYPE get(C_TYPE x) {
        if (deq.empty()) abort();
        int cur = deq.size() - 1;
        if (deq[cur].end_l <= x) return deq[cur].get(x);
        for (int i = LOG - 1; i >= 0; i--) {
            if (deq[cur].jmp[i] == -1) continue;
            if (deq[deq[cur].jmp[i]].end_l > x) cur = deq[cur].jmp[i];
        }
        cur = deq[cur].jmp[0];
        return deq[cur].get(x);
    }
};

vector<pii> adj[MAXN];
int s[MAXN], vel[MAXN];
lint ans[MAXN];
ConvexHullOpt<lint> convex;

void solve(int v, int prv, lint d) {
    // if (v != 1) {
    //     printf("v = %d:\n", v);
    //     int cur = convex.deq.size() - 1;
    //     while (cur != -1) {
    //         printf("%lld %lld\n", convex.deq[cur].a, convex.deq[cur].b);
    //         cur = convex.deq[cur].jmp[0];
    //     }
    // }
    if (v != 1) ans[v] = convex.get(vel[v]) + d*vel[v] + s[v];
    else ans[v] = 0;
    bool inserted = convex.add_line(ans[v], -d);
    for (pii edge: adj[v]) {
        int nxt, dst;
        tie(nxt, dst) = edge;
        if (nxt == prv) continue;
        solve(nxt, v, d + dst);
    }
    if (inserted) convex.deq.pop_back();
    // else printf("rejected %d\n", v);
}        

int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        adj[u].push_back(pii(v, d));
        adj[v].push_back(pii(u, d));
    }
    for (int i = 2; i <= n; i++)
        scanf("%d%d", &s[i], &vel[i]);

    solve(1, -1, 0);
    for (int i = 2; i <= n; i++)
        printf("%lld%c", ans[i], i == n ? '\n' : ' ');    
    return 0;
}
