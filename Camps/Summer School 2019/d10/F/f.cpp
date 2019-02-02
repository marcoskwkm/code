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
    freopen("farm.in", "r", stdin);
    freopen("farm.out", "w", stdout);
    int n;
    cin >> n;
    if (n % 4 == 0) printf("%d.0\n", n * n / 8);
    else if (n % 4 == 1) printf("%d.5\n", (n - 1) * (n - 1) / 8 + (n - 1) / 4 - 1);
    else if (n % 4 == 2) printf("%d.0\n", (n - 2) / 4 * ((n - 2) / 4 + 1) * 2);
    else printf("%d.5\n", ((n - 3) / 4) * ((n - 3) / 4 + 1) * 2 + (n - 3) / 4);
    return 0;
}
