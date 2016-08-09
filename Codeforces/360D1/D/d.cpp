#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;
const int MAXM = MAXN * MAXN / 2;

int eu[MAXM], ev[MAXM], c[MAXM];
int idx[MAXM];

vector<int> component[MAXN];
int cmp[MAXN];
int size[MAXN];
int color[MAXN];

void join(int i, int j) {
    if (size[cmp[i]] > size[cmp[j]]) swap(i, j);
    if (color[i] == color[j])
        for (int x: component[cmp[i]])
            color[x] ^= 1;
    int prv = cmp[i];
    for (int x: component[prv]) {
        cmp[x] = cmp[j];
        size[cmp[j]]++;
        component[cmp[j]].push_back(x);
    }
    component[prv].clear();
}        

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &eu[i], &ev[i], &c[i]);
        idx[i] = i;
    }
    sort(idx, idx + m, [](int a, int b) {
        return c[a] > c[b];
    });
    
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        for (int i = 1; i <= n; i++) {
            component[i] = vector<int>(1, i);
            cmp[i] = i;
            color[i] = 0;
            size[i] = 1;
        }
        int ans = -1;
        for (int i = 0; i < m; i++) {
            if (idx[i] < l - 1 || r - 1 < idx[i]) continue;
            int uu = eu[idx[i]], vv = ev[idx[i]];
            if (cmp[uu] != cmp[vv]) join(uu, vv);
            else if (color[uu] == color[vv]) {
                ans = c[idx[i]];
                break;
            }
        }
        printf("%d\n", ans);
    }    
    return 0;
}
