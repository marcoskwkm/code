#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

string s[MAXN];
int dist[2][MAXN];
bool done[2][MAXN];
bool seen[MAXN];

int main() {
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++)
            cin >> s[i];
        memset(dist, INF, sizeof(dist));
        memset(done, 0, sizeof(done));
        dist[0][0] = 0;
        while (1) {
            int k, v, d = INF;
            for (int i = 0; i < 2; i++) {
                for (int u = 0; u < n; u++) {
                    if (done[i][u]) continue;
                    if (dist[i][u] < d) {
                        d = dist[i][u];
                        k = i, v = u;
                    }
                }
            }
            if (d == INF) break;
            done[k][v] = 1;
            // printf("dist[%d][%d] = %d\n", k, v, dist[k][v]);
            for (int nxt = 0; nxt < n; nxt++) {
                if (v == nxt) continue;
                int cnt = 0;
                for (size_t i = 0; i < s[v].size(); i++)
                    if (s[v][i] != s[nxt][i])
                        cnt++;
                if (cnt > 2) continue;
                if (cnt == 1) dist[k][nxt] = min(dist[k][nxt], dist[k][v] + 1);
                else if (k == 0) dist[1][nxt] = min(dist[1][nxt], dist[k][v] + 2);
            }
        }
        if (dist[0][1] == INF && dist[1][1] == INF) {
            printf("0\n-1\n");
        }
        else if (dist[0][1] <= dist[1][1]) {
            printf("0\n%d\n", dist[0][1]);
        }
        else {
            string sol = "ZZZZZZZZZ";
            memset(seen, 0, sizeof(seen));
            queue<int> q;
            q.push(1);
            seen[1] = 1;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int nxt = 0; nxt < n; nxt++) {
                    if (v == nxt) continue;
                    int cnt = 0;
                    for (size_t i = 0; i < s[v].size(); i++)
                        if (s[v][i] != s[nxt][i])
                            cnt++;
                    if (cnt == 2 && dist[1][v] == dist[0][nxt] + 2) {
                        for (size_t i = 0; i < s[v].size(); i++) {
                            if (s[v][i] != s[nxt][i]) {
                                string bridge = s[v];
                                bridge[i] = s[nxt][i];
                                sol = min(sol, bridge);
                            }
                        }
                    }
                    else if (cnt == 1 && dist[1][nxt] + 1 == dist[1][v] && !seen[nxt]) {
                        q.push(nxt);
                        seen[nxt] = 1;
                    }
                }
            }            
            printf("%s\n%d\n", sol.c_str(), dist[1][1]);
        }
    }        
    return 0;
}
