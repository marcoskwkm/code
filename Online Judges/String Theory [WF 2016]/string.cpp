#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int v[MAXN];
int o[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        o[i] = v[i];
        s += v[i];
    }
    if (s & 1) {
        printf("no quotation\n");
        return 0;
    }

    for (int k = 100; k >= 1; k--) {
        for (int i = 0; i < n; i++) v[i] = o[i];
        int l = 0, r = n - 1;
        bool ok = 1;
        for (int kk = k; kk >= 1; kk--) {
            if (l > r) {
                ok = 0;
                break;
            }
            if (v[l] < kk) {
                ok = 0;
                break;
            }
            v[l] -= kk;
            if (v[l] == 0) l++;
            if (v[r] < kk) {
                ok = 0;
                break;
            }
            v[r] -= kk;
            if (v[r] == 0) r--;
        }
        if (ok) {
            if (k == 1) {
                for (int i = 0; i < n; i++)
                    if (v[i]) {
                        printf("no quotation\n");
                        return 0;
                    }
            }
            printf("%d\n", k);
            return 0;
        }
    }
    abort();
    return 0;
}
