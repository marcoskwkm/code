#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 10010;

int v[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);    
    for (int i = 0; i < n; i++) {
        int prv = (i - 1 + n) % n;
        int nxt = (i + 1) % n;
        printf("%d ", v[prv] + v[nxt]);
    }
    printf("\n");
    return 0;
}
