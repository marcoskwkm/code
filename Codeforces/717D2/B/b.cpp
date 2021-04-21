#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        vector<int> v;
        vector<int> acc;
        int xt = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            v.push_back(x);
            xt ^= x;
            acc.push_back(xt);
        }
        bool flag = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (acc[i] == (acc[n - 1] ^ acc[i])) {
                flag = 1;
            }
        }
        for (int i = 0; i + 1 < n; i++) {
            int xi = acc[i];
            for (int j = i + 1; j + 1 < n; j++) {
                int xj = acc[j] ^ acc[i];
                int xk = acc[n - 1] ^ acc[j];
                if (xi == xj && xj == xk) {
                    flag = 1;
                }
            }
        }
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}
