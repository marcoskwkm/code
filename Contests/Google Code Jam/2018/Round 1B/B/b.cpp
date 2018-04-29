// small

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

int d[MAXN], x[2][MAXN];

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &d[i], &x[0][i], &x[1][i]);
            x[1][i] *= -1;
        }
        int best = 0, cnt = 0;        
        for (int l = 0; l < n; l++) {
            int got = 0;
            for (int s = 0; s < 2; s++) {
                int r = l;
                while (r + 1 < n && d[r + 1] + x[s][r + 1] == d[l] + x[s][l])
                    r++;
                if (r + 1 < n) {
                    int other = d[r + 1] + x[s ^ 1][r + 1];
                    r++;
                    while (r + 1 < n &&
                           ((d[r + 1] + x[s ^ 1][r + 1] == other) ||
                            (d[r + 1] + x[s][r + 1] == d[l] + x[s][l])))
                        r++;
                }
                got = max(got, r - l + 1);
            }
            if (got > best) {
                best = got;
                cnt = 1;
            }
            else if (got == best) cnt++;
        }
        printf("Case #%d: %d %d\n", t, best, cnt);
    }        
    return 0;
}
