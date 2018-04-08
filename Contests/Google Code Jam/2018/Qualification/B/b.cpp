#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int v[3][MAXN];
int len[3];

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);
        int n;
        scanf("%d", &n);
        memset(len, 0, sizeof(len));
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i & 1][len[i & 1]++]);

        sort(v[0], v[0] + len[0]);
        sort(v[1], v[1] + len[1]);
        for (int i = 0; i < n; i++)
            v[2][i] = v[i & 1][i / 2];

        bool ok = 1;
        for (int i = 0; i + 1 < n; i++) {
            if (v[2][i] > v[2][i + 1]) {
                printf("%d\n", i);
                ok = 0;
                break;
            }
        }
        if (ok) printf("OK\n");
    }        
    return 0;
}
