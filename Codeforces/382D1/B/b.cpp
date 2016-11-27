#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

bool is_prime(int n) {
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0) return 0;
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    if (is_prime(n)) printf("1\n");
    else if (n % 2 == 0) printf("2\n");
    else {
        if (is_prime(n - 2)) printf("2\n");
        else printf("3\n");
    }
    return 0;
}
