#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 610;

double R[MAXN][MAXN], H[MAXN][MAXN];
double dist[MAXN][MAXN];
int n, m;
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

double get_t(int r1, int c1, int r2, int c2) {
    double R1 = R[r1][c1], R2 = R[r2][c2], H1 = H[r1][c1], H2 = H[r2][c2];
    return (R1 + R2) / 2 * exp(3.5 * fabs((H2 - H1) / 10 + 0.05));
}

void dijkstra(int sr, int sc) {
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            dist[r][c] = LINF;
    dist[sr][sc] = 0;
    set<tuple<double, int, int>> pq;
    pq.insert(make_tuple(0, sr, sc));
    while (!pq.empty()) {
        double d;
        int r, c;
        tie(d, r, c) = *pq.begin();
        pq.erase(pq.begin());
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            double t = get_t(r, c, nr, nc);
            if (dist[nr][nc] > dist[r][c] + t) {
                pq.erase(make_tuple(dist[nr][nc], nr, nc));
                dist[nr][nc] = dist[r][c] + t;
                pq.insert(make_tuple(dist[nr][nc], nr, nc));
            }
        }
    }
}

int main() {
    int p;
    cin >> n >> m >> p;
    vector<pii> v;
    for (int i = 0; i <= p; i++) {
        int r, c;
        scanf("%d%d", &r, &c);
        v.push_back(pii(r, c));
    }
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            scanf("%lf", &R[r][c]);
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            scanf("%lf", &H[r][c]);

    double ans = 0;
    for (int i = 0; i < p; i++) {
        dijkstra(v[i].first, v[i].second);
        ans += dist[v[i + 1].first][v[i + 1].second];
    }
    printf("%d\n", (int)ceil(ans));    
    return 0;
}
