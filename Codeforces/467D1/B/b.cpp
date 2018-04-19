#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<int> adj[2 * MAXN];
bool seen[2 * MAXN];
int solution[2 * MAXN];
int sol_size;

bool solve(int v) {
    seen[v] = 1;
    solution[sol_size++] = v;
    if (adj[v].empty() && (v & 1)) return 1;
    for (int nxt: adj[v]) {
        if (!seen[nxt] && solve(nxt)) return 1;
    }
    sol_size--;
    return 0;
}

bool check_draw(int v) {
    static int len = 0;
    len++;
    if (len == 1000000) return 1;
    for (int nxt: adj[v])
        if (check_draw(nxt)) return 1;
    return 0;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int v = 1; v <= n; v++) {
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int w;
            scanf("%d", &w);
            adj[2 * v].push_back(2 * w + 1);
            adj[2 * v + 1].push_back(2 * w);
        }
    }
    int s;
    cin >> s;
    if (solve(2 * s)) {
        printf("Win\n");
        for (int i = 0; i < sol_size; i++)
            printf("%d%c", solution[i] / 2, i + 1 == sol_size ? '\n' : ' ');
    }
    else printf("%s\n", check_draw(2 * s) ? "Draw" : "Lose");    
    return 0;
}
