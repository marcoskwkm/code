#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, double> pld;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

struct Bus {
    int u, v, i;
    lint s, t;
    double p;
    void read() { scanf("%d%d%lld%lld%lf", &u, &v, &s, &t, &p); }
    bool operator< (const Bus &that) const {
        return s < that.s;
    }
};

vector<Bus> buses[MAXN];
int nxt[2][MAXN];
double dp[MAXN];
vector<Bus> v;

int find(int s, lint t) {
    if (buses[s].empty()) return -1;
    int l = 0, r = buses[s].size() - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (buses[s][m].s > t) r = m;
        else l = m + 1;
    }
    if (buses[s][l].s <= t) return -1;
    return buses[s][l].i;
}

double go(int i) {
    if (i == -1) return 0;
    if (v[i].u == 1) return 1;
    if (dp[i] == dp[i]) return dp[i];
    double p1 = 0;
    int to = find(v[i].v, v[i].t);
    if (to != -1) p1 = go(to);
    double p2 = 0;
    if (nxt[1][i] != -1) p2 = go(nxt[1][i]);
    return dp[i] = max(v[i].p * p1 + (1 - v[i].p) * p2, go(nxt[0][i]));
}    

int main() {
    int m, n;
    lint k;
    cin >> m >> n >> k;

    for (int i = 0; i < m; i++) {
        Bus bus;
        bus.read();
        if (bus.u == 1) continue;
        v.push_back(bus);
    }
    Bus airport;
    airport.u = airport.v = 1;
    airport.s = airport.t = k + 1;
    v.push_back(airport);

    sort(v.begin(), v.end());
    for (int i = 0; i < (int)v.size(); i++) {
        v[i].i = i;
        buses[v[i].u].push_back(v[i]);
    }
    for (int i = 0; i < n; i++) {
        int at = 0;
        for (int j = 0; j < (int)buses[i].size(); j++) {
            nxt[0][buses[i][j].i] = (j + 1 < (int)buses[i].size() ? buses[i][j + 1].i : -1);
            while (at < (int)buses[i].size() && buses[i][at].s <= buses[i][j].s) at++;
            nxt[1][buses[i][j].i] = (at == (int)buses[i].size() ? -1 : buses[i][at].i);    
        }
    }

    if (buses[0].empty()) printf("0\n");
    else {
        memset(dp, -1, sizeof(dp));
        printf("%.9f\n", go(buses[0][0].i));
    }
    return 0;
}
