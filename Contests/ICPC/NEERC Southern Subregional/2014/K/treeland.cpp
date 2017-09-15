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

int w[MAXN][MAXN];
int ord[MAXN][MAXN];

void solve(vector<int> &s, vector<pii> &sol) {
    if (s.size() == 1) return;
    int u = s[0], v = s[1];
    for (size_t i = 2; i < s.size(); i++)
        if (ord[u][s[i]] < ord[u][v])
            v = s[i];
    sol.push_back(pii(u, v));
    vector<int> su, sv;
    for (int x: s) {
        if (ord[x][u] < ord[x][v]) su.push_back(x);
        else sv.push_back(x);
    }
    solve(su, sol), solve(sv, sol);
}    

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &w[i][j]);
                ord[i][w[i][j]] = j;
            }
        }
        vector<int> s;
        for (int i = 1; i <= n; i++)
            s.push_back(i);
        vector<pii> sol;
        solve(s, sol);
        for (pii p: sol) printf("%d %d\n", p.first, p.second);
        printf("\n");
    }
    return 0;
}
