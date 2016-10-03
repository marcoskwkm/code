#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int MAXS = MAXN;

class UnionFind {
private:
    int pai[MAXS],rank[MAXS];
    int cnt;

public:
    UnionFind(int size) {
        for (int a = 0; a < size; ++a) {
            pai[a] = a;
            rank[a] = 0;
        }
        cnt = size;
    }
    int find(int v) { return pai[v] = (pai[v]==v) ? v:find(pai[v]); }
    void join(int i,int j) {
        int pi = find(i), pj = find(j);
        if (pi == pj) return;
        --cnt;
        if (rank[pi] > rank[pj]) pai[pj] = pi;
        else if (rank[pi] < rank[pj]) pai[pi] = pj;
        else {
            pai[pj] = pi;
            rank[pi]++;
        }
    }
    bool is_connected(int i,int j) { return find(i) == find(j); }
    int count() { return cnt; }        
};

bool has_rep[MAXN][2];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pii> edges;
    UnionFind uf(n + 1);
    bool has_st = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edges.push_back(pii(u, v));
    }    
    int s, t, ds, dt;
    scanf("%d%d%d%d", &s, &t, &ds, &dt);
    for (int i = 0; i < m; i++) {
        int u, v;
        tie(u, v) = edges[i];
        if ((u == s || u == t) && (v == s || v == t)) {
            swap(edges[i], edges.back());
            edges.pop_back();
            has_st = 1;
            break;
        }
    }

    vector<pii> rem, sol;
    for (int i = 0; i < m; i++) {
        int u, v;
        tie(u, v) = edges[i];
        if (v == s || v == t) swap(u, v);
        if (u != s && u != t) {
            if (!uf.is_connected(u, v)) {
                uf.join(u, v);
                sol.push_back(pii(u, v));
            }
        }
        else rem.push_back(pii(u, v));
    }

    for (int i = 0; i < (int)rem.size(); i++) {
        int u, v;
        tie(u, v) = rem[i];
        if (u == s) has_rep[uf.find(v)][0] = 1;
        else has_rep[uf.find(v)][1] = 1;
    }

    if (!rem.empty()) {
        sort(rem.begin(), rem.end(), [&](pii a, pii b) {
            int qa = has_rep[uf.find(a.second)][0] + has_rep[uf.find(a.second)][1];
            int qb = has_rep[uf.find(b.second)][0] + has_rep[uf.find(b.second)][1];
            return qa < qb;
        });
    }

    for (int i = 0; i < (int)rem.size(); i++) {
        int u, v;
        tie(u, v) = rem[i];
        if (v != s && v != t) {
            int cmpu = uf.find(u);
            int cmpv = uf.find(v);
            if (cmpu != cmpv) {
                if (u == s && ds > 0) {
                    uf.join(u, v);
                    sol.push_back(pii(u, v));
                    ds--;
                }
                else if (u == t && dt > 0) {
                    uf.join(u, v);
                    sol.push_back(pii(u, v));
                    dt--;
                }
            }
        }
    }

    if (has_st && uf.find(s) != uf.find(t)) {
        ds--, dt--;
        sol.push_back(pii(s, t));
    }

    if ((int)sol.size() + 1 == n && ds >= 0 && dt >= 0) {
        printf("Yes\n");
        for (pii p: sol)
            printf("%d %d\n", p.first, p.second);
    }
    else printf("No\n");
    return 0;
}
