#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = (int)1e5 + 10;

vector<lint> primes;
bool sieve[MAXV];

void build() {
    for (lint p = 2; p < MAXV; p++) {
        if (sieve[p]) continue;
        primes.push_back(p);
        for (lint m = p * p; m < MAXV; m += p)
            sieve[m] = 1;
    }
}

bool is_prime(lint n) {
    for (lint p: primes) {
        if (p * p > n) break;
        if (n % p == 0) return 0;
    }
    return 1;
}        

int main() {
    build();
    lint n;
    while(scanf("%lld", &n) > 0) {
        if (is_prime(n)) {
            printf("%lld\n", n - 1);
        }
        else {
            if (n % 2 == 0)
                printf("%lld\n", n - 2);
            else {
                if (is_prime(n - 2))
                    printf("%lld\n", n - 2);
                else
                    printf("%lld\n", n - 3);
            }
        }
    }    
    return 0;
}
