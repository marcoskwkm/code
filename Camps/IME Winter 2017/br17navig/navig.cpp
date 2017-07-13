#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef pair<int, pii> pip;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

pii p[MAXN];
vector<int> adj[MAXN];
lint dist[MAXN];

void dijkstra(int s) {
    memset(dist, INF, sizeof(dist));
    dist[s] = 0;
    set<pll> pq;
    pq.insert(pii(0, s));
    while (!pq.empty()) {
        int v = pq.begin()->second;
        pq.erase(pq.begin());
        for (int nxt: adj[v]) {
            int w = min(abs(p[v].first - p[nxt].first), abs(p[v].second - p[nxt].second));
            if (dist[nxt] > dist[v] + w) {
                pq.erase(pll(dist[nxt], nxt));
                dist[nxt] = dist[v] + w;
                pq.insert(pll(dist[nxt], nxt));
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<pip> v;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].first, &p[i].second);
        v.push_back(pip(i, p[i]));
    }
    sort(v.begin(), v.end(), [](pip a, pip b) {
        return a.second.first < b.second.first;
    });
    for (int i = 1; i < n; i++) {
        adj[v[i].first].push_back(v[i - 1].first);
        adj[v[i - 1].first].push_back(v[i].first);
    }
    sort(v.begin(), v.end(), [](pip a, pip b) {
        return a.second.second < b.second.second;
    });
    for (int i = 1; i < n; i++) {
        adj[v[i].first].push_back(v[i - 1].first);
        adj[v[i - 1].first].push_back(v[i].first);
    }
    dijkstra(0);
    printf("%lld\n", dist[n - 1]);    
    return 0;
}
