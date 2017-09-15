#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = (int)1e5 + 10;
const int ROOT = 320;

struct UnionFind {
    vector<int> prv, rnk, parity;
    stack<int> ok;
    stack<pii> history;

    UnionFind(int n) {
        prv.resize(n, -1), rnk.resize(n, 0), parity.resize(n);
        ok.push(1);
    }

    void join(int u, int v) {
        // debug("join %d %d\n", u, v);
        int ru, pu, rv, pv;
        tie(ru, pu) = find(u);
        tie(rv, pv) = find(v);
        // debug("%d %d %d %d\n", ru, pu, rv, pv);
        if (ru == rv) {
            history.push(pii(-1, -1));
            if (pu == pv) ok.push(0);
            else ok.push(ok.top());
        }
        else {
            if (rnk[ru] > rnk[rv]) {
                swap(ru, rv);
                swap(pu, pv);
            }
            prv[ru] = rv;
            parity[ru] = pu ^ pv ^ 1;
            if (rnk[ru] == rnk[rv]) {
                rnk[rv]++;
                history.push(pii(ru, 1));
            }
            else history.push(pii(ru, 0));
            ok.push(ok.top());
        }
    }

    pii find(int v) {
        int k = 0;
        while (prv[v] != -1) {
            k ^= parity[v];
            v = prv[v];
        }
        return pii(v, k);
    }

    void undo_join() {
        pii p = history.top();
        history.pop();
        ok.pop();
        if (p.first != -1) {
            if (p.second == 1) rnk[prv[p.first]]--;
            prv[p.first] = -1;
        }
    }

    bool is_ok() { return ok.top(); }
};

int u[MAXM], v[MAXM];
int ans[MAXM];

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++)
        scanf("%d%d", &u[i], &v[i]);
    vector<tiii> queries;
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--, r--;
        queries.push_back(tiii(l, r, i));
    }
    sort(queries.begin(), queries.end(), [](tiii a, tiii b) {
        return get<1>(a) < get<1>(b);
    });
    
    memset(ans, -1, sizeof(ans));
    for (int x = ROOT; x < m; x += ROOT) {
        UnionFind uf(n + 1);
        int at = x;
        for (const tiii &query: queries) {
            int l, r, id;
            tie(l, r, id) = query;
            // debug("query %d %d %d\n", l, r, id);
            if (l < x - ROOT || l >= x || r < x) continue;
            while (at <= r) {
                uf.join(u[at], v[at]);
                at++;
            }
            for (int j = x - 1; j >= l; j--)
                uf.join(u[j], v[j]);
            ans[id] = uf.is_ok();
            for (int j = x - 1; j >= l; j--)
                uf.undo_join();
        }
    }

    for (const tiii &query: queries) {
        int l, r, id;
        tie(l, r, id) = query;
        if (ans[id] != -1) continue;
        // debug("query %d %d %d\n", l, r, id);
        vector<int> x;
        for (int i = l; i <= r; i++) {
            x.push_back(u[i]);
            x.push_back(v[i]);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        map<int, int> mp;
        for (size_t i = 0; i < x.size(); i++)
            mp[x[i]] = i;
            
        UnionFind uf(x.size());
        for (int i = l; i <= r; i++)
            uf.join(mp[u[i]], mp[v[i]]);
        ans[id] = uf.is_ok();
    }
    for (int i = 0; i < q; i++)
        printf("%s\n", ans[i] ? "Possible" : "Impossible");
    return 0;
}
