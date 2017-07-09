#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 10010;

int n, k;
int bit[MAXN];
int last[MAXN];
inline void bit_update(int i) {
    for(; i <= n; i += i & -i) {
        if (last[i] != k) bit[i] = 0;
        bit[i]++;
        last[i] = k;
    }
}

inline int bit_query(int i) {
    int ret = 0;
    for(; i > 0; i -= i & -i) {
        if (last[i] != k) bit[i] = 0;
        ret += bit[i];
        last[i] = k;
    }
    return ret;
}

int v[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    lint best = LINF;
    int ans = -1;
    for (k = 1; 2*k <= n; k++) {
        if (n % k) continue;
        lint got = 0;
        for (int i = n; i >= 1; i--) {
            int bucket = (v[i] - 1) / k + 1;
            got += bit_query(bucket - 1);
            bit_update(bucket);
            if (got * k >= best) break;
        }
        got *= k;
        if (got < best) {
            best = got;
            ans = k;
        }
    }
    cout << ans << " " << best << endl;        
    return 0;
}
