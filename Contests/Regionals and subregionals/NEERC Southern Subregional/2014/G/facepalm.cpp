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

int v[MAXN], sol[MAXN];

int main() {
    int n, k;
    cin >> n >> k;
    int low = INF;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        low = min(low, v[i]);
        sol[i] = v[i];
    }
    lint cur_sum = 0;
    for (int i = 0; i < k; i++)
        cur_sum += v[i];
    lint rem = max(0LL, cur_sum + 1);
    lint ans = 0;
    for (int i = k - 1; i >= 0; i--) {
        lint take = min<lint>(sol[i] - low, rem);
        sol[i] -= take;
        rem -= take;
        cur_sum -= take;
        ans += take;
    }
    for (int i = k; i < n; i++) {
        cur_sum += sol[i] - sol[i - k];
        lint take = max(0LL, cur_sum + 1);
        sol[i] -= take;
        ans += take;
        cur_sum -= take;
    }
    printf("%lld\n", ans);
    for (int i = 0; i < n; i++)
        printf("%d ", sol[i]);
    printf("\n");    
    return 0;
}
