#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        bool ok = n & 1;
        for (int i = 0; i < n; i++) {
            int h;
            scanf("%d", &h);
            if (h != min(i + 1, n - i)) ok = 0;
        }
        printf("%s\n", ok ? "yes" : "no");
    }            
    return 0;
}
