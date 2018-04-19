#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXC = 30;

bool reach[MAXC][MAXC];
vector<int> adj[MAXC];

void dfs(int v, int s) {
    reach[s][v] = 1;
    for (int nxt: adj[v])
        if (!reach[s][nxt])
            dfs(nxt, s);
}

int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        char u, v;
        scanf(" %c %c", &u, &v);
        adj[u - 'a'].push_back(v - 'a');
    }
    for (int i = 0; i < MAXC; i++) dfs(i, i);
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        bool ok = (a.size() == b.size());
        for (int j = 0; j < (int)a.size(); j++)
            if (!reach[a[j] - 'a'][b[j] - 'a'])
                ok = 0;
        printf("%s\n", ok ? "yes" : "no");
    }
    return 0;
}
