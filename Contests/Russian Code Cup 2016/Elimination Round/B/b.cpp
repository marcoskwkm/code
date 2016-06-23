#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = (int)2e5 + 10;

int bit[MAXM];
int n, m;

int query(int i) {
    i++;
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret += bit[i];
    return ret;
}

void update(int i, int v) {
    i++;
    for (; i <= 2*m; i += i & -i)
        bit[i] += v;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        scanf("%d%d", &n, &m);
        vector<pii> notes;
        set<int> rs;
        for (int i = 0; i <= 2*m; i++)
            bit[i] = 0;
        for (int i = 0; i < m; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            if (l + r > n) continue;
            rs.insert(r);
            rs.insert(n - l);
            notes.push_back(pii(l, r));
        }
        sort(notes.begin(), notes.end());
        map<int, int> mpr;
        int cnt = 0;
        for (int r: rs) mpr[r] = cnt++;
        assert(cnt <= 2*m);
        
        int ans = 0;
        int al = 1;
        for (pii p: notes) {
            int l = p.first;
            int got = query(mpr[n - l]);
            if (got + 1 > ans) {
                ans = got + 1;
                al = l;
            }
            update(mpr[p.second], 1);
        }
        printf("%d %d\n", al, n - al);
    }        
    return 0;
}
