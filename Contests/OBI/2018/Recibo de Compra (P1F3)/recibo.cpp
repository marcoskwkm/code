#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int f(int q, int n, int last) {
    if (n == 1) return q > last;
    int ret = 0;
    for (int take = last + 1; take * n <= q; take++)
        ret += f(q - take, n - 1, take);
    return ret;
}

int main() {
    int R, K;
    cin >> R >> K;
    printf("%d\n", f(R, K, 0));    
    return 0;
}
