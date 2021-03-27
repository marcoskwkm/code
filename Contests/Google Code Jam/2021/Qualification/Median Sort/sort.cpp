#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

vector<int> ord;

void go(int l, int r, int i) {
    // debug("go(%d, %d, %d)\n", l, r, i);
    if (r < l) {
        ord.insert(ord.begin() + r + 1, i);
        // debug("order:");
        // for (int x: ord) debug(" %d", x);
        // debug("\n");
        return;
    } else if (l == r) {
        if (l > 0) {
            go(l - 1, r, i);
        } else {
            go(l, r + 1, i);
        }
        return;
    }

    int len = r - l + 1;
    int rem = len - 2;
    int third = rem / 3;
    int ml = l + third + (rem % 3 > 0 ? 1 : 0);
    int mr = ml + third + (rem % 3 > 1 ? 1 : 0) + 1;
    // debug("len = %d, third = %d, ml = %d, mr = %d\n", len, third, ml, mr);
    printf("%d %d %d\n", ord[ml], ord[mr], i);
    fflush(stdout);
    int median;
    scanf("%d", &median);
    if (median == -1) {
        exit(0);
    } else if (median == ord[ml]) {
        go(l, ml - 1, i);
    } else if (median == ord[mr]) {
        go(mr + 1, r, i);
    } else {
        go(ml + 1, mr - 1, i);
    }
}

int main() {
    int t = 1, T, N, Q;
    for (scanf("%d%d%d", &T, &N, &Q); t <= T; t++) {
        ord = {1, 2};
        for (int i = 3; i <= N; i++) {
            go(0, i - 2, i);
        }
        for (int i = 0; i < N; i++) {
            printf("%d%c", ord[i], i + 1 == N ? '\n' : ' ');
        }
        fflush(stdout);
        int result;
        scanf("%d", &result);
        if (result == -1) {
            return 0;
        }
    }
    return 0;
}
