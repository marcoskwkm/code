#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXK = 42;

int n, k;
int primes[MAXK];

int go(lint prod, bool add, int i) {
    if (prod > n) return 0;
    if (i == k) {
        int q = n / prod;
        return add ? q : -q;
    }
    
    int ret = go(prod, add, i + 1) + go(prod * primes[i], !add, i + 1);
    return ret;
}    

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++)
        scanf("%d", &primes[i]);
    sort(primes, primes + k);
    printf("%d\n", go(1, 1, 0));    
    return 0;
}
