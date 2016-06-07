#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e5 + 10;

int v[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    multiset<int> s;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        s.insert(v[i]);
    }
    sort(v, v + n);
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (2 * mid > n) r = mid - 1;
        else {
            bool ok = 1;
            for (int i = 0; i < mid; i++) {
                if (2 * v[mid - 1 - i] > v[n - 1 - i]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) l = mid;
            else r = mid - 1;
        }
    }
    printf("%d\n", n - l);        
    return 0;
}
