#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int N = 7;
const lint P[] = {16, 9, 5, 7, 11, 13, 17};
lint A[N], B[N];

pll bezout(lint a, lint b, lint m) {
    if (b == 0) return pll(1, 0);
    pll p = bezout(b, a % b, m);
    return pll(p.second % m, (p.first - (a / b) * p.second) % m);
}

lint inverse(lint a, lint m) {
    a %= m;
    lint ret = bezout(a, m, m).first;
    return (ret % m + m) % m;
}

int main() {
    int t = 1, T;
    for (scanf("%d%*d%*d", &T); t <= T; t++) {
        lint prod = 1;
        for (int i = 0; i < N; i++) {
            prod *= P[i];
            for (int j = 0; j < 18; j++)
                printf("%lld ", P[i]);
            printf("\n");
            fflush(stdout);

            A[i] = 0;
            for (int j = 0; j < 18; j++) {
                int got;
                scanf("%d", &got);
                if (got == -1) return 0;
                A[i] += got;
            }
            A[i] %= P[i];                
        }

        lint ans = 0;
        for (int i = 0; i < N; i++) {
            B[i] = inverse(prod / P[i], P[i]);
            ans += ((prod / P[i] * B[i]) % prod) * A[i];
        }

        printf("%lld\n", ans % prod);
        debug("%lld\n", ans % prod);
        fflush(stdout);

        int verdict;
        scanf("%d", &verdict);
        
        if (verdict == -1)
            return 0;
    }    
    return 0;
}
