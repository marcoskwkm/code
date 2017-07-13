#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

pii operator+ (pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, m, nn, mm;
        scanf("%d%d%d%d", &n, &m, &nn, &mm);
        set<pii> grid;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                char p;
                scanf(" %c", &p);
                if (p == 'x') grid.insert(pii(r, c));
            }
        }
        vector<pii> stamp;
        for (int r = 0; r < nn; r++) {
            for (int c = 0; c < mm; c++) {
                char p;
                scanf(" %c", &p);
                if (p == 'x') {
                    stamp.push_back(pii(r, c));
                }
            }
        }
        sort(stamp.begin(), stamp.end());
        pii first = stamp[0];
        for (pii &p: stamp) {
            p.first -= first.first;
            p.second -= first.second;
        }
        bool ok = 1;
        while (!grid.empty() && ok) {
            pii start = *grid.begin();
            for (int i = 0; i < (int)stamp.size(); i++) {
                pii p = start + stamp[i];
                if (grid.find(p) == grid.end()) {
                    ok = 0;
                    break;
                }
                grid.erase(p);
            }
        }
        printf("%s\n", ok ? "ANO" : "NIE");
    }        
    return 0;
}
