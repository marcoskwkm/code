#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 1010, MAXN = 310;

vector<int> adj[MAXN];
vector<pii> island[MAXN];
bool done[MAXN];

void dfs(int v, vector<int> &s) {
    s.push_back(v);
    done[v] = 1;
    for (int nxt: adj[v])
        if (!done[nxt])
            dfs(nxt, s);
}

int solve(const vector<int> &s) {
    int l = 0, r = 200000;
    while (l < r) {
        int mid = (l + r) / 2;
        int rem = mid;
        for (int i: s) {
            for (pii p: island[i]) {
                if (p.first == 0 || p.second < mid) continue;
                rem -= p.first;
            }
        }
        if (rem < 0) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    int n, f, d;
    cin >> n >> f >> d;
    for (int i = 0; i < f; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < d; i++) {
        int id, s, g;
        scanf("%d%d%d", &id, &s, &g);
        island[id].push_back(pii(s, g));
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (done[i]) continue;
        vector<int> s;
        dfs(i, s);
        ans += solve(s);
    }

    printf("%d\n", ans);        
    return 0;
}
