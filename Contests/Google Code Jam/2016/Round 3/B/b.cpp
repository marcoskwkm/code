#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110, MAXM = 10;
const int NREP = (int)2e4;

int n, m;
vector<int> adj[MAXN];
int cnt[MAXM];
char letter[MAXN];
string cool[MAXM];
vector<int> avail;
string str;
int qv[MAXN];
int total;

void dfs(int v) {
    qv[v] = 1;
    for (int nxt: adj[v]) {
        dfs(nxt);
        qv[v] += qv[nxt];
    }
}

void go() {
    if (avail.empty()) {
        for (int i = 0; i < m; i++) {
            if (str.find(cool[i]) != string::npos)
                cnt[i]++;
        }
        return;
    }
    int i = rand() % total;
    int cur = 0;
    int idx;
    for (idx = 0; cur + qv[avail[idx]] <= i; cur += qv[avail[idx++]]);
    int v = avail[idx];
    swap(avail[idx], avail.back());
    total -= qv[v];
    avail.pop_back();
    for (int nxt: adj[v]) {
        avail.push_back(nxt);
        total += qv[nxt];
    }
    if (v) str += letter[v];
    go();
}    

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        scanf("%d", &n);
        for (int v = 0; v <= n; v++) adj[v].clear();
        for (int v = 1; v <= n; v++) {
            int u;
            scanf("%d", &u);
            adj[u].push_back(v);
        }
        for (int v = 1; v <= n; v++)
            scanf(" %c", &letter[v]);
        scanf("%d",  &m);
        for (int i = 0; i < m; i++)
            cin >> cool[i];

        dfs(0);
        memset(cnt, 0, sizeof(cnt));
        for (int rep = 0; rep < NREP; rep++) {
            avail = {0};
            total = n + 1;
            str = "";
            go();
        }
        printf("Case #%d:", t);
        for (int i = 0; i < m; i++)
            printf(" %.3f", double(cnt[i]) / NREP);
        printf("\n");
    }
    return 0;
}
