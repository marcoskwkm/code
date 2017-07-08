#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint f[40];

char go(int n, int k) {
    if (n < 3) return (k == 1 ? 'a' + n : 'z');
    if (f[n - 1] >= k) return go(n - 1, k);
    else if (f[n - 1] + f[n - 2] >= k) return go(n - 2, k - f[n - 1]);
    else if (f[n - 1] + f[n - 2] + f[n - 3] >= k)
        return go(n - 3, k - f[n - 1] - f[n - 2]);
    return 'z';
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    f[0] = f[1] = f[2] = 1;
    for (int i = 3; i <= 35; i++) {
        f[i] = f[i - 1] + f[i - 2] + f[i - 3];
    }

    char ans = go(n, k);
    if (ans == 'z') printf("-1\n");
    else printf("%c\n", ans);
    return 0;
}
