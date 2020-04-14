#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXB = 32;

bool take[MAXB];

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        memset(take, 0, sizeof(take));

        int n;
        cin >> n;

        int highest = 0;
        for (int i = 30; i >= 0; i--) {
            if (n >= (1 << i) + i) {
                take[i] = 1;
                n -= (1 << i);
                highest = max(highest, i);
            } else if (highest > i) {
                n--;
            }
        }

        assert(take[0]);

        printf("Case #%d:\n", t);
        printf("1 1\n");
        int side = 0;
        for (int i = 1; i <= highest; i++) {
            printf("%d %d\n", i + 1, side == 0 ? 1 : i + 1);
            if (take[i]) {
                if (side == 0) {
                    for (int j = 2; j <= i + 1; j++) printf("%d %d\n", i + 1, j);
                } else {
                    for (int j = i; j >= 1; j--) printf("%d %d\n", i + 1, j);
                }
                side ^= 1;
            }
        }

        while (n--) {
            ++highest;
            printf("%d %d\n", highest + 1, side == 0 ? 1 : highest + 1);
        }
    }
    return 0;
}
