#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

int q[3];

lint ch(lint n, int k) {
    lint ret = 1;
    for (int i = 0; i < k; i++)
        ret *= n - i;
    for (int i = 1; i <= k; i++)
        ret /= i;
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x == 1) q[1]++;
        else if (x > 1) q[2]++;
    }
    lint ans = 0;
    // 3 colors
    ans += ch(q[2], 3);

    // 4 colors
    ans += ch(q[1], 2) * ch(q[2], 2);
    ans += q[1] * ch(q[2], 3) * 3;
    ans += ch(q[2], 4) * ch(4, 2);

    // 5 colors
    ans += q[2] * ch(q[1], 4) * 3;
    ans += ch(q[2], 2) * 2 * ch(q[1], 3) * 3;
    ans += ch(q[2], 3) * 3 * ch(q[1], 2) * 3;
    ans += ch(q[2], 4) * 4 * ch(q[1], 1) * 3;
    ans += ch(q[2], 5) * 5 * 3;

    // 6 colors
    ans += ch(q[1] + q[2], 6) * 5 * 3 * 2;

    printf("%lld\n", ans);
    return 0;
}
