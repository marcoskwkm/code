#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef unsigned long long ulint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

namespace MillerRabin {
    typedef unsigned long long ulint;
    vector<ulint> magic = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    ulint prod(ulint a, ulint b, ulint m) {
        ulint ret = 0, p = a;
        while (b) {
            if (b & 1) ret = (ret + p) % m;
            p = 2 * p % m;
            b >>= 1;
        }
        return ret;
    }

    ulint modexp(ulint b, ulint e, ulint m) {
        ulint ret = 1, p = b;
        while (e) {
            if (e & 1) ret = prod(ret, p, m);
            p = prod(p, p, m);
            e >>= 1;
        }
        return ret;
    }

    // O(log^2 n), works for any n < 2^63
    bool is_prime(ulint n) {
        if (n < 1) return 0;
        ulint d = n - 1;
        int s = 0;
        while (!(d & 1)) d >>= 1, s++;
        for (const ulint &a: magic) {
            if (n == a) return 1;
            ulint ad = modexp(a, d, n);
            if (ad == 1) continue;
            bool composite = 1;
            for (int r = 0; r < s; r++) {
                if (ad == n - 1) {
                    composite = 0;
                    break;
                }
                ad = prod(ad, ad, n);
            }
            if (composite) return 0;
        }
        return 1;
    }
}

void solve() {
    ulint n;
    cin >> n;

    ulint l = 1, r = n;
    while (l < r) {
        __int128 m = (l + r + 1) / 2;
        if (m * m > n) {
            r = m - 1;
        } else {
            l = m;
        }
    }

    vector<__int128> primes;
    while (l > 1 && primes.size() < 2) {
        if (MillerRabin::is_prime(l)) {
            primes.push_back(l);
        }
        l--;
    }
    while (true) {
        ++r;
        if (MillerRabin::is_prime(r)) {
            primes.push_back(r);
            break;
        }
    };

    if (primes.size() == 2) {
        cout << " " << ulint(primes[0] * primes[1]) << endl;
    } else {
        __int128 cand1 = primes[0] * primes[1], cand2 = primes[0] * primes[2];
        if (cand2 <= n) {
            cout << " " << ulint(cand2) << endl;
        } else {
            cout << " " << ulint(cand1) << endl;
        }
    }
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        solve();
    }
    return 0;
}
