#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int B_SIZE = 550;
const int MAXN = (int)3e5 + 10;

int v[MAXN];
tiii queries[MAXN];
int freq[MAXN];
int freqfreq[MAXN];
int ans[MAXN];

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        queries[i] = tiii(l - 1, r - 1, i);
    }

    sort(queries, queries + q, [](tiii a, tiii b) {
        auto [la, ra, _] = a;
        auto [lb, rb, __] = b;
        if (la / B_SIZE != lb / B_SIZE) {
            return la < lb;
        }
        return ra < rb;
    });

    int cr = -1, cl = 0;
    int maxfreq = 0;
    for (int qi = 0; qi < q; qi++) {
        auto [l, r, i] = queries[qi];
        // debug("query %d\n", i);

        while (cr < r) {
            cr++;
            int &f = freq[v[cr]];
            freqfreq[f]--;
            f++;
            freqfreq[f]++;
            maxfreq = max(maxfreq, f);
        }
        while (cr > r) {
            int &f = freq[v[cr]];
            freqfreq[f]--;
            if (freqfreq[f] == 0 && maxfreq == f) {
                maxfreq--;
            }
            f--;
            freqfreq[f]++;
            cr--;
        }
        while (cl < l) {
            int &f = freq[v[cl]];
            freqfreq[f]--;
            if (freqfreq[f] == 0 && maxfreq == f) {
                maxfreq--;
            }
            f--;
            freqfreq[f]++;
            cl++;
        }
        while (cl > l) {
            cl--;
            int &f = freq[v[cl]];
            freqfreq[f]--;
            f++;
            freqfreq[f]++;
            maxfreq = max(maxfreq, f);
        }

        // debug("f = %d\n", maxfreq);
        int len = r - l + 1;
        int x = maxfreq, y = len - maxfreq;
        ans[i] = 1 + max(0, x - (y + 1));
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
