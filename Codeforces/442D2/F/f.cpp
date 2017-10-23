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
int fp[4 * MAXN], fm[4 * MAXN];

int n, k;

lint cur = 0;
int cl, cr;

void add_r(int i) {
    fp[id[i][1]]++;
    fm[id[i - 1][1]]++;
    cur += fm[id[i][0]];    
}

void rem_r(int i) {
    cur -= fm[id[i][0]];
    fp[id[i][1]]--;
    fm[id[i - 1][1]]--;
}

void add_l(int i) {
    fp[id[i][1]]++;
    fm[id[i - 1][1]]++;
    cur += fp[id[i - 1][2]];
}

void rem_l(int i) {
    cur -= fp[id[i - 1][2]];
    fp[id[i][1]]--;
    fm[id[i - 1][1]]--;
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
    }
    for (int i = 0; i <= n; i++) {
        cj.insert(acc[i]);
        cj.insert(acc[i] - k);
        cj.insert(acc[i] + k);
    }
    map<lint, int> comp;
    int foo = 0;
    for (lint x: cj) comp[x] = foo++;
    for (int i = 0; i <= n; i++) {
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

    cl = 1, cr = 0;
    for (tiii query: queries) {
        int l, r, i;
        tie(l, r, i) = query;
        while (cr < r) add_r(++cr);
        while (cl < l) rem_l(cl++);
        while (cr > r) rem_r(cr--);
        while (cl > l) add_l(--cl);
        ans[i] = cur;
        // debug("query %d %d = %lld\n", l, r, cur);
    }
    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);
    
    return 0;
}
