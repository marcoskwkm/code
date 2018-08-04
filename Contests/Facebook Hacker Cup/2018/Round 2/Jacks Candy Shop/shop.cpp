#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int q[MAXN];
vector<int> child[MAXN];
set<int, greater<int>> candies[MAXN];
int idx[MAXN];

lint go(int v) {
    lint ret = 0;
    for (int nxt: child[v]) {
        ret += go(nxt);
        if (candies[idx[nxt]].size() > candies[idx[v]].size())
            idx[v] = idx[nxt];
    }
    for (int nxt: child[v]) {
        if (idx[nxt] == idx[v]) continue;
        for (int candy: candies[idx[nxt]])
            candies[idx[v]].insert(candy);
        candies[idx[nxt]].clear();
    }
    candies[idx[v]].insert(v);
    while (q[v] > 0 && !candies[idx[v]].empty()) {
        q[v]--;
        ret += *candies[idx[v]].begin();
        candies[idx[v]].erase(candies[idx[v]].begin());
    }
    return ret;
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n, m;
        lint a, b;
        cin >> n >> m >> a >> b;
        for (int v = 0; v < n; v++) {
            q[v] = 0;
            child[v].clear();
            candies[v].clear();
            idx[v] = v;
        }
        for (int i = 0; i < m; i++)
            q[(a * i + b) % n]++;
        for (int v = 1; v < n; v++) {
            int p;
            scanf("%d", &p);
            child[p].push_back(v);
        }
        printf("Case #%d: %lld\n", t, go(0));
    }        
    return 0;
}
