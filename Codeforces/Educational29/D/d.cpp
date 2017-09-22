#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<int, int, int> Query;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int MAXM = 110;

int v[MAXN];
int b[MAXM];

int main() {
    int n, q, m;
    cin >> n >> q >> m;
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    vector<Query> queries;
    for (int i = 0; i < q; i++) {
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        queries.push_back(Query(k, l, r));
    }
    for (int i = 0; i < m; i++)
        scanf("%d", &b[i]);

    reverse(queries.begin(), queries.end());
    for (const Query &query: queries) {
        int k, l, r;
        tie(k, l, r) = query;
        if (k == 1) {
            for (int i = 0; i < m; i++) {
                if (b[i] == l) b[i] = r;
                else if (l < b[i] && b[i] <= r)
                    b[i]--;
            }
        }
        else {
            for (int i = 0; i < m; i++) {
                if (l <= b[i] && b[i] <= r) {
                    b[i] = r + l - b[i];
                }
            }
        }
    }
    for (int i = 0; i < m; i++)
        printf("%d%c", v[b[i] - 1], i + 1 == m ? '\n' : ' ' );        
    return 0;
}
