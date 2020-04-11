#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int mat[MAXN][MAXN];

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                scanf("%d", &mat[r][c]);

        int k = 0, rr = 0, rc = 0;
        for (int i = 0; i < n; i++)
            k += mat[i][i];

        for (int i = 0; i < n; i++) {
            set<int> setr, setc;
            bool flagr = 0, flagc = 0;
            for (int j = 0; j < n; j++) {
                if (setr.find(mat[i][j]) != setr.end()) {
                    flagr = 1;
                }
                if (setc.find(mat[j][i]) != setc.end()) {
                    flagc = 1;
                }
                setr.insert(mat[i][j]);
                setc.insert(mat[j][i]);
            }
            rr += flagr;
            rc += flagc;
        }

        printf("Case #%d: %d %d %d\n", t, k, rr, rc);
    }
    return 0;
}
