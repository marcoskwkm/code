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
const int MAXN = (int)1e5 + 10;
const int MAXQ = (int)5e5 + 10;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// Supports *find_by_order() and order_of_key()
template<class T> using OrderedSet = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

OrderedSet<pii> s[MAXN];
int w[MAXN];
int id[MAXN];
int ans[MAXQ];

struct Query {
    int i, d, s, k;
    Query(int _i, int _d, int _s, int _k) : i(_i), d(_d), s(_s), k(_k) {}
    bool operator< (const Query &that) const {
        return d < that.d;
    }
};

void add_edge(int u, int v) {
    if (id[u] == id[v]) return;
    if (s[id[u]].size() < s[id[v]].size()) swap(u, v);
    int rem = id[v];
    for (const pii &p: s[rem]) {
        s[id[u]].insert(p);
        id[p.second] = id[u];
    }
    s[rem].clear();
}

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        s[i].insert(pii(-w[i], i));
        id[i] = i;
    }
    vector<pip> edges;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        edges.push_back(pip(c, pii(u, v)));
    }
    sort(edges.begin(), edges.end());

    vector<Query> queries;
    for (int i = 0; i < q; i++) {
        int v, d, k;
        scanf("%d%d%d", &v, &d, &k);
        queries.push_back(Query(i, d, v, k));
    }
    sort(queries.begin(), queries.end());

    int at = 0;
    for (const Query &query: queries) {
        // debug("query: %d %d %d\n", query.s, query.d, query.k);
        while (at < m && edges[at].first <= query.d) {
            // debug("add_edge (%d, %d) %d\n", edges[at].second.first, edges[at].second.second, edges[at].first);
            add_edge(edges[at].second.first, edges[at].second.second);
            at++;
        }
        int i = id[query.s];
        // debug("can reach:");
        // for (pii p: s[i]) debug(" %d", p.second);
        // debug("\n");
        if ((int)s[i].size() < query.k) ans[query.i] = -1;
        else ans[query.i] = -s[i].find_by_order(query.k - 1)->first;
    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);    
    return 0;
}
