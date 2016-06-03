#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector< vector<int> > mat(n);
    map<int, int> freq[2];
    int cur = 0, prv = 1;
    bool ok = 1;
    for (int r = 0; r < n; r++) {
        mat[r] = vector<int>(m);
        for (int c = 0; c < m; c++) {
            scanf("%d", &mat[r][c]);
            int f = ++freq[cur][mat[r][c]] + freq[prv][mat[r][c]];
            if (f > m) {
                ok = 0;
            }
        }
        if (!ok) break;
        if (r) {
            set<pii, greater<pii>> sc, sp;
            debug("r = %d:\n", r);
            debug("cur:\n");
            for (pii p: freq[cur]) {
                debug("%d: %d\n", p.first, p.second);
                sc.insert(pii(p.second, p.first));
            }
            debug("prev:\n");
            for (pii p: freq[prv]) {
                debug("%d: %d\n", p.first, p.second);
                sp.insert(pii(p.second, p.first));
            }
            multiset<pii> pairs;
            for (int i = 0; i < m; i++) {
                pii top_c = *sc.begin(), top_p = *sp.begin();
                sc.erase(sc.begin());
                sp.erase(sp.begin());
                if (top_c.second == top_p.second) {
                    if(top_c.first > top_p.first) {
                        pii tmp = top_p;
                        top_p = *sp.begin();
                        sp.insert(tmp);
                    }
                    else {
                        pii tmp = top_c;
                        top_c = *sc.begin();
                        sc.insert(tmp);
                    }
                }
                pairs.insert(pii(top_p.second, top_c.second));
                if (top_c.first - 1) sc.insert(pii(top_c.first - 1, top_c.second));
                if (top_p.first - 1) sp.insert(pii(top_p.first - 1, top_p.second));
            }
            // for (pii p: pairs) debug("%d - %d\n", p.first, p.second);
            for (int i = 0; i < m; i++) {
                auto it = pairs.lower_bound(pii(mat[r - 1][i], 0));
                pairs.erase(it);
                mat[r][i] = it->second;
            }
        }
        // debug("finished r = %d\n", r);
        freq[prv].clear();
        cur ^= 1;
        prv ^= 1;
    }
    if (!ok) printf("-1\n");
    else {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++)
                printf("%d ", mat[r][c]);
            printf("\n");
        }
    }   
    return 0;
}
