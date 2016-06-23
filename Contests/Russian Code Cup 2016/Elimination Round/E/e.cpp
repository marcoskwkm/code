#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<pii, int> ppi;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int SQ = 400;

int val[MAXN];
lint ans[MAXN];

lint bit[MAXN];

inline void bit_add(int i, int v) {
    assert(i);
    for (; i < MAXN; i += i & -i)
        bit[i] += v;
}

lint bit_query(int i) {
    lint ret = 0;
    for (; i > 0; i -= i & -i)
        ret += bit[i];
    return ret;
}

struct Query {
    int l, r, i;
    lint s;
    Query(int ll, int rr, int ii, lint ss) {
        l = ll, r = rr, i = ii, s = ss;
    }
    bool operator< (const Query &that) const {
        if (s == that.s) return i < that.i;
        return s < that.s;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pii> v;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        v.push_back(pii(val[i], i));
    }
    sort(v.begin(), v.end());
    
    set<Query> queries;
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        queries.insert(Query(l, r, i, 0));
    }

    fill(ans, ans + m, 1);
    int at = 0;
    while (!queries.empty()) {
        Query cur = *queries.begin();
        queries.erase(queries.begin());
        while (at < n && v[at].first <= cur.s + 1) {
            bit_add(v[at].second, v[at].first);
            at++;
        }

        lint news = bit_query(cur.r) - bit_query(cur.l - 1);
        if (news == cur.s) continue;
        ans[cur.i] = news + 1;
        queries.insert(Query(cur.l, cur.r, cur.i, news));
    }
    
    for (int i = 0; i < m; i++)
        printf("%lld\n", ans[i]);    
    return 0;
}
