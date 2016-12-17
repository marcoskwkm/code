#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

vector<int> adj[MAXN];
int size[MAXN];
int cmp[MAXN];

void dfs(int v, int i) {
    cmp[v] = i;
    size[i]++;
    for (int nxt: adj[v])
        if (cmp[nxt] == -1)
            dfs(nxt, i);
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> homes;
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        homes.push_back(x);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int total = 0;
    int largest = 0;
    memset(cmp, -1, sizeof(cmp));
    for (int i = 0; i < k; i++) {
        dfs(homes[i], i);
        total += size[i] * (size[i] - 1) / 2;
        if (size[i] > size[largest])
            largest = i;
    }

    for (int v = 1; v <= n; v++)
        if (cmp[v] == -1)
            total += size[largest]++;

    printf("%d\n", total - m);    
    return 0;
}

