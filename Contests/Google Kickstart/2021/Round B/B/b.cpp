#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

void solve() {
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }

    vector<int> jmp_r(n), val_r(n), jmp_l(n), val_l(n);
    jmp_l[0] = 0;
    val_l[0] = 0;
    for (int i = 1; i < n; i++) {
        val_l[i] = v[i] - v[i - 1];
        if (val_l[i] == val_l[i - 1]) {
            jmp_l[i] = jmp_l[i - 1];
        } else {
            jmp_l[i] = i - 1;
        }
    }
    jmp_r[n - 1] = n - 1;
    val_r[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
        val_r[i] = v[i] - v[i + 1];
        if (val_r[i] == val_r[i + 1]) {
            jmp_r[i] = jmp_r[i + 1];
        } else {
            jmp_r[i] = i + 1;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            int r = jmp_r[i], l = i - 1;
            int x = v[i] + val_r[i];
            if (i + 1 > 0 && v[i - 2] - x == val_r[i]) {
                l = i - 2;
                if (val_l[i - 2] == -val_r[i]) {
                    l = jmp_l[i - 2];
                }
            }
            ans = max(ans, r - l + 1);
        }
        if (i + 1 < n) {
            int l = jmp_l[i], r = i + 1;
            int x = v[i] + val_l[i];
            if (i + 2 < n && v[i + 2] - x == val_l[i]) {
                r = i + 2;
                if (val_r[i + 2] == -val_l[i]) {
                    r = jmp_r[i + 2];
                }
            }
            ans = max(ans, r - l + 1);
        }
    }

    printf(" %d\n", ans);
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        solve();
    }
    return 0;
}
