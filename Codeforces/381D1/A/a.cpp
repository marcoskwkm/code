#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int v[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(v, -1, sizeof(v));
    vector<pii> v;
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        v.push_back(pii(l, r));
    }
    sort(v.begin(), v.end(), [](pii a, pii b) {
        return a.second - a.first < b.second - b.first;
    });

    int ans = v[0].second - v[0].first + 1;
    printf("%d\n", ans);
    for (int i = 0; i < n; i++)
        printf("%d%c", i % ans, i + 1 == n ? '\n' : ' ');    
    return 0;
}
