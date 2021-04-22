#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        string sa, sb, sc;
        cin >> sa >> sb >> sc;
        int qa0 = count(sa.begin(), sa.end(), '0');
        int qa1 = 2 * n - qa0;
        int qb0 = count(sb.begin(), sb.end(), '0');
        int qb1 = 2 * n - qb0;
        int qc0 = count(sc.begin(), sc.end(), '0');
        int qc1 = 2 * n - qc0;

        string sx, sy;
        char target;
        if (max(min(qa0, qb0), min(qa1, qb1)) >= n) {
            sx = sa, sy = sb;
            if (min(qa0, qb0) >= n) {
                target = '0';
            } else {
                target = '1';
            }
        } else if (max(min(qa0, qc0), min(qa1, qc1)) >= n) {
            sx = sa, sy = sc;
            if (min(qa0, qc0) >= n) {
                target = '0';
            } else {
                target = '1';
            }
        } else {
            sx = sb, sy = sc;
            if (min(qb0, qc0) >= n) {
                target = '0';
            } else {
                target = '1';
            }
        }

        int ix = 0, iy = 0;
        while (ix < 2 * n && iy < 2 * n) {
            if (sx[ix] == sy[iy]) {
                printf("%c", sx[ix]);
                iy++, ix++;
            } else {
                if (sy[iy] != target) {
                    printf("%c", sy[iy]);
                    iy++;
                } else {
                    printf("%c", sx[ix]);
                    ix++;
                }
            }
        }
        while (ix < 2 * n) {
            printf("%c", sx[ix++]);
        }
        while (iy < 2 * n) {
            printf("%c", sy[iy++]);
        }
        printf("\n");
    }
    return 0;
}
