#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110, MAXM = 1010;

vector<pii> adj[MAXN];
int value[MAXN];
int dist[MAXN];
pii prv[MAXN];
int edge_value[MAXM];

void explore(int v) {
    for (pii edge: adj[v]) {
        int w, i;
        tie(w, i) = edge;
        if (prv[w].first == -1) {
            prv[w] = pii(v, i);
        }
    }
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n, m;
        cin >> n >> m;
        for (int v = 1; v <= n; v++) {
            adj[v].clear();
            prv[v] = pii(-1, -1);
        }

        vector<int> pos, neg;
        for (int i = 2; i <= n; i++) {
            scanf("%d", &value[i]);
            if (value[i] > 0) pos.push_back(i);
            else neg.push_back(i);
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(pii(v, i));
            adj[v].push_back(pii(u, i));
            edge_value[i] = 1000000;
        }

        sort(pos.begin(), pos.end(), [](int i, int j) { return value[i] < value[j]; });
        sort(neg.begin(), neg.end(), [](int i, int j) { return -value[i] < -value[j]; });

        vector<int> seq;
        size_t at = 0;
        for (size_t i = 0; i < pos.size(); i++) {
            while (at < neg.size() && int(seq.size() + 1) >= -value[neg[at]]) {
                seq.push_back(neg[at++]);
            }
            seq.push_back(pos[i]);
            while (i + 1 < pos.size() && value[pos[i + 1]] == value[pos[i]]) {
                seq.push_back(pos[++i]);
            }
        }
        while (at < neg.size()) seq.push_back(neg[at++]);

        prv[1] = pii(0, 0);
        dist[1] = 0;
        explore(1);
        int last = -1;
        for (int v: seq) {
            assert(prv[v].first != -1);

            if (value[v] > 0) {
                assert(dist[prv[v].first] < value[v]);
                dist[v] = value[v];
                edge_value[prv[v].second] = dist[v] - dist[prv[v].first];
            } else {
                dist[v] = dist[prv[v].first] + 1;
                if (last != -1) {
                    dist[v] = max(dist[v], dist[last]);
                    if (value[last] > 0 || (value[last] < 0 && value[last] != value[v])) {
                        dist[v] = max(dist[v], dist[last] + 1);
                    }
                }
                edge_value[prv[v].second] = dist[v] - dist[prv[v].first];
            }

            last = v;
            explore(v);
        }

        printf("Case #%d:", t);
        for (int i = 0; i < m; i++) printf(" %d", edge_value[i]);
        printf("\n");
    }
    return 0;
}
