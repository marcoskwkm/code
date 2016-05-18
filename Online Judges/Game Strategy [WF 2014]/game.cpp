#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 26;

int dist[MAXN];
vector<int> options[MAXN];
int ans[MAXN][MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int q;
        for (scanf("%d", &q); q--;) {
            string s;
            cin >> s;
            int mask = 0;
            for (char c: s) mask |= (1 << (c - 'a'));
            options[i].push_back(mask);
        }
    }
    for (int i = 0; i < n; i++) {
        memset(dist, -1, sizeof(dist));
        dist[i] = 0;
        int reach = (1 << i);
        int nxt_reach = reach;
        bool stop = 0;
        for (int d = 1; !stop; d++) {
            stop = 1;
            for (int j = 0; j < n; j++) {
                if (dist[j] != -1) continue;
                bool get = 0;
                for (int op: options[j]) {
                    if ((op & reach) == op) {
                        get = 1;
                        break;
                    }
                }
                if (get) {
                    dist[j] = d;
                    nxt_reach |= (1 << j);
                    stop = 0;
                }
            }
            reach = nxt_reach;
        }
        for (int j = 0; j < n; j++)
            ans[j][i] = dist[j];        
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf("%d%c", ans[i][j], " \n"[j + 1 == n]);
    return 0;
}
