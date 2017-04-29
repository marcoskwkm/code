#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        lint n;
        scanf("%lld", &n);
        for (int q = 1;; q++) {
            if (__builtin_popcountll(q * n) <= q) {
                printf("%d", q);
                lint m = q * n;
                multiset<lint, greater<lint>> s;
                while (m) {
                    s.insert(__builtin_ctzll(m));
                    m -= m & -m;
                }
                bool ok = 1;
                while (s.size() < q) {
                    int k = *s.begin();
                    if (k == 0) {
                        ok = 0;
                        break;
                    }
                    s.erase(s.begin());
                    s.insert(k - 1);
                    s.insert(k - 1);
                }
                if (!ok) continue;
                for (int k: s) printf(" %d", k);
                printf("\n");
                break;
            }
        }
    }
    return 0;
}
