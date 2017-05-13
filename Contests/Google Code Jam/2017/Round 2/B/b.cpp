#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;
const int MAXC = 1010;

int q_cust[MAXC];
int q_pos[MAXN];

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        printf("Case #%d: ", t);
        memset(q_cust, 0, sizeof(q_cust));
        memset(q_pos, 0, sizeof(q_pos));
        int n, c, m;
        scanf("%d%d%d", &n, &c, &m);
        int min_rides = 0;
        for (int i = 0; i < m; i++) {
            int b, p;
            scanf("%d%d", &p, &b);
            min_rides = max(min_rides, ++q_cust[b]);
            q_pos[p]++;
        }
        int sum = 0;
        for (int pos = 1; pos <= n; pos++) {
            sum += q_pos[pos];
            min_rides = max(min_rides, (sum + pos - 1) / pos);
        }
        int min_upg = 0;
        for (int pos = 1; pos <= n; pos++)
            min_upg += max(0, q_pos[pos] - min_rides);
        printf("%d %d\n", min_rides, min_upg);
    }        
    return 0;
}
