#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXP = (int)2e6 + 10;

vector<int> primes;
bool sieve[MAXP];

void build_sieve() {
    for (lint p = 2; p < MAXP; p++) {
        if (sieve[p]) continue;
        primes.push_back(p);
        for (lint m = p*p; m < MAXP; m += p)
            sieve[m] = 1;
    }
}

int main() {
    build_sieve();
    int t;
    cin >> t;
    lint a, b;
    scanf("%lld%lld", &a, &b);
    vector<lint> v(b - a + 1);
    for (lint i = a; i <= b; i++)
        v[i - a] = i;
    vector<lint> nd(b - a + 1, 1);
    for (int p: primes) {
        lint s = a - a % p;
        if (s < a) s += p;
        while (s <= b) {
            int k = 0;
            do {
                v[s - a] /= p;
                k++;
            } while (v[s - a] % p == 0);
            nd[s - a] *= (k + 1);
            s += p;
        }
    }
    for (lint i = a; i <= b; i++)
        if (v[i - a] > 1)
            nd[i - a] *= 2;
    while (t--) {
        lint d;
        scanf("%lld", &d);
        lint ans = 0;
        for (lint i = a; i <= b; i++) {
            lint x = i;
            int k = 0;
            while (x % d == 0) {
                k++;
                x /= d;
            }
            ans += nd[i - a] / (k + 1);
        }
        printf("%lld\n", ans);
    }        
    return 0;
}
