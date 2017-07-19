#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 3010;

int s[3][MAXN];
vector<int> vv[3][MAXN];

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        for (int k = 0; k < 3; k++)
            for (int i = 0; i < n; i++)
                scanf("%d", &s[k][i]);
        for (int k = 0; k < 3; k++) {
            for (int v = 1; v <= n; v++)
                vv[k][v].clear();
            for (int i = 0; i < n; i++)
                vv[k][s[k][i]].push_back(i);
        }        
        vector<tiii> equal;
        for (int v = 1; v <= n; v++)
            for (int i: vv[0][v])
                for (int j: vv[1][v])
                    for (int k: vv[2][v])
                        equal.push_back(tiii(i, j, k));

        sort(equal.begin(), equal.end());
        vector<int> len(equal.size());
        for (int i = 0; i < (int)equal.size(); i++) {
            for (int j = 0; j < (int)equal.size(); j++) {
                int a, b, c, x, y, z;
                tie(a, b, c) = equal[i];
                tie(x, y, z) = equal[j];
                if (a < x && b < y && c < z) len[j] = max(len[j], len[i] + 1);
            }
        }
        printf("%d\n", *max_element(len.begin(), len.end()) + 1);
    }        
    return 0;
}
