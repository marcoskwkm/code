#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

bool is_prime(int n) {
    for (int d = 2; d*d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n > 2 && !is_prime(n)) n--;
    printf("%d\n", n);
    return 0;
}
