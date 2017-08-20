#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, x;
    cin >> n >> x;
    bool lo = 0, hi = 0;
    for (int i = 0; i < n; i++) {
        int q;
        scanf("%d", &q);
        if (q == x) {
            printf("1\n");
            return 0;
        }
        else if (q < x) lo = 1;
        else hi = 1;
    }
    printf("%d\n", (lo && hi) ? 2 : -1);
    return 0;
}
