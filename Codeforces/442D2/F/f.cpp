#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int SQ = 173;

int t[MAXN], v[MAXN];
lint acc[MAXN];
lint ans[MAXN];
int id[MAXN][3];
int freq[MAXN];

int n, k;

lint cur = 0;
int cl, cr;

void add_r(int i) {
    cur += freq[id[i][0]];
    freq[id[i][1]]++;
    // debug("f[%lld]++\n", acc[i]);
    // debug("add_r %d: cur = %lld\n", i, cur);
}

void rem_r(int i) {
    freq[id[i][1]]--;
    cur -= freq[id[i][0]];
}

void add_l(int i) {
    cur += freq[id[i][2]];
    freq[id[i][1]]++;
}

void rem_l(int i) {
    freq[id[i][1]]--;
    cur -= freq[id[i][2]];
    // debug("f[%lld]--\n", acc[i]);
    // debug("rem_r %d: cur = %lld\n", i, cur);
}    

int main() {
    cin >> n >> k;
    set<lint> cj;
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        if (t[i] == 2) v[i] *= -1;
        acc[i] = acc[i - 1] + v[i];
        cj.insert(acc[i]);
        cj.insert(acc[i] - k);
        cj.insert(acc[i] + k);
    }
    cj.insert(0);
    map<lint, int> comp;
    int foo = 0;
    for (lint x: cj) comp[x] = foo++;
    for (int i = 1; i <= n; i++) {
        id[i][0] = comp[acc[i] - k];
        id[i][1] = comp[acc[i]];
        id[i][2] = comp[acc[i] + k];
    }
    
    vector<tiii> queries;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        queries.push_back(tiii(l, r, i));
    }
    sort(queries.begin(), queries.end(), [](tiii a, tiii b) {
        int a1, a2, a3, b1, b2, b3;
        tie(a1, a2, a3) = a; tie(b1, b2, b3) = b;
        if (a1 / SQ == b1 / SQ) return a2 > b2;
        return a1 / SQ < b1 / SQ;
    });

    freq[comp[0]] = 1;
    cl = 1, cr = 0;
    for (tiii query: queries) {
        int l, r, i;
        tie(l, r, i) = query;
        while (cr < r) add_r(++cr);
        while (cr > r) rem_r(cr--);
        while (cl < l) rem_l(cl++);
        while (cl > l) add_l(--cl);
        ans[i] = cur;
        // debug("query %d %d = %lld\n", l, r, cur);
    }
    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);
    
    return 0;
}
