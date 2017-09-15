#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const double PI = acos(-1.0);

int v[MAXN], u[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    sort(v, v + n);
    int l = 0, r = n - 1;
    for (int i = 0; i < n; i++) {
        if (i & 1) u[r--] = v[i];
        else u[l++] = v[i];
    }
    double ans = 0;
    for (int i = 0; i < n; i++)
        ans += u[i] * u[(i + 1)%n];

    printf("%.3f\n", ans * sin(2*PI / n) / 2);
    return 0;
}
