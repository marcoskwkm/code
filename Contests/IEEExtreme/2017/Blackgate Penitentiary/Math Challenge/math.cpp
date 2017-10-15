#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;
const int MOD = (int)1e9 + 7;

vector<int> primes;
bool sieve[MAXN];

void build_factors() {
    for (lint p = 2; p < MAXN; p++) {
        if (sieve[p]) continue;
        primes.push_back(p);
        for (lint m = p * p; m < MAXN; m += p)
            sieve[m] = 1;
    }
}

int count(int l, int r, int p) {
    int ret = 0;
    int s = l - l % p;
    if (s < l) s += p;
    for (int i = s; i <= r; i += p) {
        int x = i;
        do {
            ret++;
            x /= p;
        } while (x % p == 0);
    }
    return ret;
}

lint modexp(lint b, int e, int mod) {
    lint ret = 1;
    while (e) {
        if (e & 1) ret = ret * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return ret;
}

int choose(int n, int k, int mod) {
    k = min(k, n - k);
    lint ret = 1;
    for (int p: primes) {
        int q = count(k + 1, n, p) - count(2, n - k, p);
        ret = ret * modexp(p, q, mod) % mod;
    }    
    return ret;
}

int main() {
    build_factors();
    int t;
    for (cin >> t; t--;) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << modexp(a, choose(b, c, MOD - 1), MOD) << endl;
    }        
    return 0;
}
