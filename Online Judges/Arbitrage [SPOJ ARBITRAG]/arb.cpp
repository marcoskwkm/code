#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 50;
const long double EPS = 0;

vector< pair<int, long double> > adj[MAXN];
long double cst[MAXN];

bool bellman_ford(int n) {
    for (int i = 0; i < n; i++)
        cst[i] = 1;

    for (int i = 0; i < n; i++) {
        for (int v = 0; v < n; v++) {
            for (pair<int, long double> edge: adj[v]) {
                int nxt;
                long double c;
                tie(nxt, c) = edge;
                if (cst[nxt] > cst[v] + c + EPS) {
                    if (i + 1 == n) return 1;
                    cst[nxt] = cst[v] + c;
                }
            }
        }
    }
    return 0;
}            

int main() {
    int n, t = 1;
    while (scanf("%d", &n) && n) {
        map<string, int> mp;
        for (int i = 0; i < n; i++) {
            string name;
            cin >> name;
            mp[name] = i;
            adj[i].clear();
        }
        int m;
        for (scanf("%d", &m); m--;) {
            string su, sv;
            long double c;
            cin >> su >> c >> sv;
            adj[mp[su]].push_back(make_pair(mp[sv], -log(c)));
        }
        printf("Case %d: %s\n", t++, bellman_ford(n) ? "Yes" : "No");
    }        
    return 0;
}
