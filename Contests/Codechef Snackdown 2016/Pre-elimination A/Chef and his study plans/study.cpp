#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int LOG = 20;

pii course[MAXN];
int low[MAXN];
int nxt[LOG][MAXN];

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &course[i].first, &course[i].second);
    sort(course, course + n, [](pii a, pii b) {
        return a.second < b.second;
    });
    int at = 0;
    low[0] = course[0].first;
    for (int i = 0; i < n; i++) {
        while (at < n && course[i].second >= course[at].first) at++;
        nxt[0][i] = at;
        low[i] = max(low[i - 1], course[i].first);
    }
    nxt[0][n] = n;
    for (int i = 1; i < LOG; i++)
        for (int j = 0; j <= n; j++)
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];

    low[n] = course[n].first = course[n].second = INF;
    while (q--) {
        int start, end;
        scanf("%d%d", &start, &end);
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) / 2;
            if (low[mid] >= start) r = mid;
            else l = mid + 1;
        }
        if (course[l].second > end) {
            printf("0\n");
            continue;
        }
        int ans = 1;
        for (int i = LOG - 1; i >= 0; i--) {
            if (course[nxt[i][l]].second <= end) {
                l = nxt[i][l];
                ans += (1 << i);
            }
        }
        printf("%d\n", ans);
    }    
    return 0;
}
