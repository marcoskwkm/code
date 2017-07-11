#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;
const int MAGIC = 200;

lint v[MAXN];
lint rem[MAXN];
lint add[MAXN];
int n, k;

bool check(lint q) {
    // printf("Check %lld\n", q);
    memset(rem, 0, sizeof(rem));
    rem[k] = q;
    for (int i = 0; i < n; i++) {
        lint got = v[i];
        memset(add, 0, sizeof(add));
        for (int j = k; j >= 0; j--) {
            lint take = min(got, rem[j]);
            got -= take;
            rem[j] -= take;
            add[j - 1] += take;
        }
        for (int j = 1; j < k; j++)
            rem[j] += add[j];
    }
    for (int i = 1; i <= k; i++) {
        // printf("rem[%d] = %lld\n", i, rem[i]);
        if (rem[i] > 0)
            return 0;
    }
    return 1;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            scanf("%lld", &v[i]);
        if (k == 1) {
            printf("%lld\n", accumulate(v, v + n, 0LL));
            continue;
        }
        sort(v, v + n, greater<lint>());
        
        lint l = 0, r = 6000000000000000000LL;
        while (l < r) {
            lint mid = (l + r + 1) / 2;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        cout << l << endl;
    }            
    return 0;
}
