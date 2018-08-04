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
        printf("Case #%d: ", t);
        int n, k;
        cin >> n >> k;
        if (n == 2 || k <= 2) {
            printf("0\n");
            printf("1\n1 %d 1\n", n);
            continue;
        }
        vector<tiii> edges;
        edges.push_back(tiii(1, n, k));
        int ans = -k;
        for (int v = 2, len = k - 1; v <= n && len > 0; v++, len--) {
            edges.push_back(tiii(v - 1, (len == 1) ? n : v, len));
            ans += len;
        }
        printf("%d\n%d\n", ans, (int)edges.size());
        for (tiii edge: edges) {
            int u, v, c;
            tie(u, v, c) = edge;
            printf("%d %d %d\n", u, v, c);
        }
    }        
    return 0;
}
