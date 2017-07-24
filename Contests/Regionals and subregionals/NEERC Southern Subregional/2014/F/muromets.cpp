#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int f[MAXN];
int acc[MAXN], hi[MAXN];;

int main() {
    int n, k;
    cin >> n >> k;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &f[i]);
        sum += f[i];
    }
    if (2 * k >= n) {
        printf("%d\n", sum);
        return 0;
    }
    sum = 0;
    for (int i = 0; i < k; i++)
        sum += f[i];
    acc[k - 1] = hi[k - 1] =sum;
    for (int i = k; i < n; i++) {
        sum += f[i] - f[i - k];
        acc[i] = sum;
        hi[i] = max(hi[i - 1], sum);
    }
    int ans = 0;
    for (int i = 2 * k - 1; i < n; i++)
        ans = max(ans, acc[i] + hi[i - k]);

    cout << ans << endl;
    return 0;
}
