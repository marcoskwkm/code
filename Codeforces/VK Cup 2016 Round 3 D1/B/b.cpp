#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, k;
    int a, b, c, d;
    scanf("%d%d%d%d%d%d", &n, &k, &a, &b, &c, &d);
    vector<int> left;
    for (int v = 1; v <= n; v++) {
        if (v == a || v == b || v == c || v == d) continue;
        left.push_back(v);
    }
    if (left.empty() || k < n + 1) {
        printf("-1\n");
        return 0;
    }
    
    printf("%d %d", a, c);
    for (int v: left) printf(" %d", v);
    printf(" %d %d\n", d, b);

    printf("%d %d", c, a);
    for (int v: left) printf(" %d", v);
    printf(" %d %d\n", b, d);               
        
    return 0;
}
