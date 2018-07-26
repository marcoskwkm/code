#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2010;

int l[MAXN], r[MAXN], label[MAXN];
int pos_idx[MAXN];
bool seen[MAXN];
vector<int> pre, pos;

void dfs(int v) {
    pre.push_back(v);
    if (l[v]) dfs(l[v]);
    if (r[v]) dfs(r[v]);
    pos_idx[v] = pos.size();
    pos.push_back(v);
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        int n, k;
        cin >> n >> k;
        for (int v = 1; v <= n; v++)
            cin >> l[v] >> r[v];
        pre.clear(), pos.clear();
        dfs(1);
        
        memset(seen, 0, sizeof(seen));
        int n_cycles = 0;
        for (int i = 0; i < n; i++) {
            if (seen[i]) continue;
            n_cycles++;
            int idx = i;
            do {
                seen[idx] = 1;
                label[pre[idx]] = min(n_cycles, k);
                idx = pos_idx[pre[idx]];
            } while (!seen[idx]);
        }
        if (n_cycles < k) printf(" Impossible\n");
        else {
            for (int v = 1; v <= n; v++)
                printf(" %d", label[v]);
            printf("\n");
        }
    }        
    return 0;
}
