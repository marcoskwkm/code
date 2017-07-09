#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <queue>
#define pb push_back
#define MAXN 300
#define EPS 1e-8
#define INF 1e18
using namespace std;

vector <int> g[MAXN];
vector <double> w[MAXN];
map <pair <int, int>, int> mapa;
double d[MAXN];

int node = 0;
int xa[MAXN];
int ya[MAXN];

void add_edge(int a, int b, double cost) {
    g[a].pb(b);
    w[a].pb(cost);
    g[b].pb(a);
    w[b].pb(cost);
    return;
}

void dijkstra(int s, int n) {
    priority_queue <pair<double, int> > pq;
    for (int i = 0; i < n; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    pq.push(make_pair(0, s));
    while(!pq.empty()) {
        double cost = -pq.top().first;
        int next = pq.top().second;
        pq.pop();

        if (cost - d[next] > EPS) {
            continue;
        }

        for (int i = 0; i < (int)g[next].size(); i++) {
            int viz = g[next][i];
            if (d[viz] > d[next] + w[next][i] + EPS) {
                d[viz] = d[next] + w[next][i];
                pq.push(make_pair(-d[viz], viz));
            }
        }
    }
    return;
}
    
    
double dist(int x1, int y1, int x2, int y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

int main(void) {
    int x, y;

    scanf(" %d %d", &x, &y);
    xa[node] = x;
    ya[node] = y;
    mapa[make_pair(x, y)] = node++; 
    scanf(" %d %d", &x, &y);
    xa[node] = x;
    ya[node] = y;
    mapa[make_pair(x, y)] = node++;

    while(scanf(" %d %d", &x, &y) != EOF) {
        int sx = x;
        int sy = y;
        pair <int, int> p = make_pair(x, y);
        if (mapa.find(p) == mapa.end()) {
            mapa[p] = node++;
        }
        int idx = mapa[p];
        xa[idx] = x;
        ya[idx] = y;

        while(scanf(" %d %d", &x, &y) && !(x == -1 && y == -1)) {
            pair <int, int> p = make_pair(x, y);
            if (mapa.find(p) == mapa.end()) {
                mapa[p] = node++;
            }
            int id2 = mapa[p];
            xa[id2] = x;
            ya[id2] = y;
            add_edge(idx, id2, dist(sx, sy, x, y) / 40);
            idx = id2;
            sx = x, sy = y;
        }
    }

    // printf("node = %d\n", node);
    for (int i = 0; i < node; i++) {
        // printf("i = %d, xa = %d, ya = %d\n", i, xa[i], ya[i]);
        for (int j = i + 1; j < node; j++) {
            add_edge(i, j, dist(xa[i], ya[i], xa[j], ya[j]) / 10);
        }
    }

    dijkstra(0, node);
    printf("%.0f\n", (d[1] * 60) / 1000);
    return 0;
}
