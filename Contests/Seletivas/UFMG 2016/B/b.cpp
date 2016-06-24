#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

int main() {
    int n;
    scanf("%d", &n);
    int ans = 0, flip = 0;
    for (int i = 0; i < n - 1; i++) {
        int x;
        scanf("%d", &x);
        if (flip) x ^= 1;
        if (!x) {
            flip = 1;
            ans++;
        }
        else flip = 0;
    }
    int x;
    scanf("%d", &x);
    if (x ^ flip == 0) ans = -1;
    printf("%d\n", ans);
    return 0;
}
        
