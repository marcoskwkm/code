#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55;

int mat[MAXN][MAXN];

int main() {
    for (int n = 6; n <= 50; n++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                mat[r][c] = 1 + (r + c) % n;
            }
        }
        vector<bool> found(n * n + 1, 0);
        int left = n * n - n - 1; // excludes n + 1 and n**2 - 1

        vector<int> rp, cp, np;
        for (int i = 0; i < n; i++) {
            rp.push_back(i);
            cp.push_back(i);
            np.push_back(i);
        }

        debug("n = %d...\n", n);

        while (left > 0) {
            int trace = 0;
            for (int i = 0; i < n; i++) {
                trace += np[mat[rp[i]][cp[i]] - 1] + 1;
            }
            if (!found[trace]) {
                found[trace] = 1;
                left--;
            }
            random_shuffle(np.begin(), np.end());
            random_shuffle(rp.begin(), rp.end());
            random_shuffle(cp.begin(), cp.end());
        }

        if (left == 0) {
            debug("Found solution for all cases\n");
        } else {
            debug("Solution missing for following k:");
            for (int k = n + 2; k < n * n - 1; k++) {
                if (!found[k]) {
                    debug(" %d", k);
                }
            }
            debug("\n");
        }

        debug("\n");
    }
    return 0;
}
