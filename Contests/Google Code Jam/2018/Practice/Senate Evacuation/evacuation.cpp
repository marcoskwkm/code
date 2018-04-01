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
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        cin >> n;
        set<pii, greater<pii>> s;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int q;
            cin >> q;
            s.insert(pii(q, i));
            sum += q;
        }
        printf("Case #%d:", t);
        if (sum & 1) {
            pii p = *s.begin();
            s.erase(s.begin());
            printf(" %c", 'A' + p.second);
            if (--p.first > 0) s.insert(p);
        }
        for (int x = 1; !s.empty(); x ^= 1) {
            if (x) printf(" ");
            pii p = *s.begin();
            s.erase(s.begin());
            printf("%c", 'A' + p.second);            
            if (--p.first > 0) s.insert(p);
        }
        printf("\n");
    }        
    return 0;
}
