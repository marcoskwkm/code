#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 22;

vector<pair<pii, int>> day[MAXD];

int main() {
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        day[k - 1].push_back(make_pair(pii(l, r), i + 1));
    }
    for (int k = 0; k < d; k++) {
        int il, ir;
        int l = 0, r = INF;
        for (size_t i = 0; i < day[k].size(); i++) {
            if (day[k][i].first.first > l) {
                l = day[k][i].first.first;
                il = day[k][i].second;
            }
            if (day[k][i].first.second < r) {
                r = day[k][i].first.second;
                ir = day[k][i].second;
            }
        }
        if (l > r) printf("ANO %d %d\n", ir, il);
        else printf("NIE\n");
    }        
    return 0;
}
