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
        int top = deq.size() - 1;
        if (top != -1) {
            for (int i = LOG - 1; i >= 0; i--) {
                int aux = deq[top].jmp[i];
                if (aux == -1) continue;
                if (deq[aux].end_l > cross(newline, deq[aux]))
                    top = aux;
            }
            if (deq[top].end_l > cross(newline, deq[top]))
                top = deq[top].jmp[0];
        }
        if (top >= 0) newline.end_l = cross(newline, deq[top]);
        newline.jmp[0] = top;
        for (int i = 1; i < LOG; i++) {
            int aux = newline.jmp[i - 1];            
            newline.jmp[i] = (aux == -1 ? -1 : deq[aux].jmp[i - 1]);
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
