#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 1010;
const int MAXV = MAXD * MAXD;

int to[MAXV];
char grid[MAXD][MAXD];
int n, m;
int indeg[MAXV];
bool done[MAXV];
vector<int> rev[MAXV];
vector<tiii> ans;
bool seen[MAXV];
int cycle_len[MAXV];
int nxt_avail;

void dfs(int v, int t, int g, int len) {
    seen[v] = 1;
    if (nxt_avail == len) return;
    int r = v / m, c = v % m;
    if (isupper(grid[r][c])) {
        int tt = nxt_avail - t;
        if (tt <= 0) tt += len;
        // printf("(%d, %d)(%d) takes %d\n", r + 1, c + 1, t, nxt_avail);
        ans.push_back(tiii(r + 1, c + 1, tt));
        nxt_avail++;
    }
    for (int nxt: rev[v])
        if (!seen[nxt])
            dfs(nxt, (t + 1) % len, g, len);    
}        

int main() {
    cin >> n >> m;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            scanf(" %c", &grid[r][c]);
            int nr = r, nc = c;
            if (tolower(grid[r][c]) == 'n') nr--;
            else if (tolower(grid[r][c]) == 'e') nc++;
            else if (tolower(grid[r][c]) == 'w') nc--;
            else nr++;
            int u = r * m + c, v = nr * m + nc;
            to[u] = v;
            indeg[v]++;
            rev[v].push_back(u);
        }
    }
    queue<int> q;
    for(int i = 0; i < n * m; i++)
        if (indeg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        done[v] = 1;
        if (--indeg[to[v]] == 0)
            q.push(to[v]);
    }

    for (int i = 0; i < n * m; i++) {
        if (done[i] || cycle_len[i] > 0) continue;
        int cnt = 0;
        int cur = i;
        do {
            cnt++;
            cur = to[cur];
        } while (cur != i);
        for (int j = 0; j < cnt; j++) {
            cycle_len[cur] = cnt;
            cur = to[cur];
        }
    }            

    for (int i = 0; i < n * m; i++) {
        if (done[i]) continue;
        // printf("Start cycle at (%d, %d)\n", i / m + 1, i % m + 1);
        nxt_avail = 0;
        dfs(i, 0, i + 1, cycle_len[i]);
        int cur = to[i];
        while (!done[cur]) {
            done[cur] = 1;
            cur = to[cur];
        }
    }
    printf("%d\n", (int)ans.size());
    for (tiii p: ans) {
        int r, c, t;
        tie(r, c, t) = p;
        printf("%d %d %d\n", r, c, t);
    }
    return 0;
}
