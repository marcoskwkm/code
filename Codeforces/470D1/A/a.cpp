#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXP = (int)1e6 + 10;

int sieve[MAXP];
vector<int> primes;

void build_sieve() {
    for (lint p = 2; p < MAXP; p++) {
        if (sieve[p]) continue;
        primes.push_back(p);
        for (lint q = 2 * p; q < MAXP; q += p)
            sieve[q] = p;
    }
}

int main() {
    build_sieve();
    
    lint n;
    cin >> n;
    int maxp;
    for (int p: primes)
        if (n % p == 0)
            maxp = p;

    int ans = n;
    for (int x = n - maxp + 1; x <= n; x++) {
        ans = min(ans, max(3,  x - sieve[x] + 1));
    }

    cout << ans << endl;
    return 0;
}
