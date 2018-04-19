#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10;

int deg[MAXN];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        deg[u]++;
        deg[v]++;
    }

    vector<int> v;
    for (int i = 0; i < n; i++)
        v.push_back(i);

    sort(v.begin(), v.end(), [](int a, int b) { return deg[a] < deg[b]; });
    int sum = 2 * m;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int rem = sum - 2 * (n - 1);
        int to = max(1, deg[v[i]] - rem);
        if (to != deg[v[i]]) ans++;
        sum -= deg[v[i]] - to;
        deg[v[i]] = to;
        if (sum == 2 * (n - 1)) break;
    }
    printf("%d\n%d %d\n", ans, n, n - 1);

    sort(v.begin(), v.end(), [](int a, int b) { return deg[a] < deg[b]; });
    // for (int i = 0; i < n; i++)
    //     printf("deg[%d] = %d\n", v[i], deg[v[i]]);
    int at = 0;
    while (deg[v[at]] <= 1 && at + 1 < n) at++;
    for (int i = 0; i + 1 < n; i++) {
        assert(deg[v[i]] == 1);
        printf("%d %d\n", v[i], v[at]);
        deg[v[i]]--, deg[v[at]]--;
        if (deg[v[at]] == 1 && at + 1 < n) at++;
    }
    
    return 0;
}
