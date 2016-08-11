#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int cst[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &cst[i]);
    sort(cst, cst + n);
    
    int q;
    for (scanf("%d", &q); q--;) {
        int x;
        scanf("%d", &x);
        printf("%d\n", x < cst[0] ? 0 : upper_bound(cst, cst + n, x) - cst);
    }
    return 0;
}
