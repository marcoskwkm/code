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
    int v, n;
    cin >> v >> n;
    for (int k = 1; k <= 9; k++)
        printf("%d%c", (n * v * k + 9) / 10, k == 9 ? '\n' : ' ');
    
    return 0;
}
