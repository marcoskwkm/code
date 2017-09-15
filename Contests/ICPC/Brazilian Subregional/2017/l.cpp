#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

inline lint modexp(lint b, lint e, lint m) {
    lint ret = 1;
    while (e) {
        if (e & 1) ret = ret * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return ret;
}

// mod P = c*2^k + 1
// r is primitive root of P
lint v2[1 << 23];
void NTT(vector<int> &v, int type, int k, int c, int r) {
    int P = (1 << k) * c + 1;
    int n = v.size();
    while (n & (n - 1)) { v.push_back(0); n++; }
    int logn = __builtin_ctz(n);
    for (int i = 0; i < n; i++) {
        int mask = 0;
        int x = i;
        while (x) {
            int bit = x & -x;
            mask |= (1 << (logn - 1 - __builtin_ctz(bit)));
            x ^= bit;
        }
        v2[mask] = v[i];
    }
    for (int s = 0, m = 2; s < logn; s++, m <<= 1) {
        lint wm = modexp(r, c * (1 << (k - (s + 1))), P);
        if (type == -1) wm = modexp(wm, P - 2, P);
        v[0] = 1;
        for (int i = 1; 2 * i < m; i++)
            v[i] = wm * v[i - 1] % P;
        for (int i = 0; i < n; i += m) {
            for (int j = 0; 2 * j < m; j++) {
                int t = v[j] * v2[i + j + (m >> 1)] % P;
                v2[i + j + (m >> 1)] = v2[i + j] - t;
                v2[i + j] = v2[i + j] + t;
            }
        }
    }
    // if (type == -1) {
    //     lint invn = modexp(n, P - 2, P);
    //     for (lint &x: v2) {
    //         x = (x * invn) % P;
    //         if (x < 0) x += P;
    //     }
    // }
    // else for (lint &x: v2) {
    //     if (x < 0) x = x % P + P;
    //     else x %= P;
    // }
}        
    
int main() {
    const int K = 23, C = 20;
    const int P = C * (1 << K) + 1;
    string s;
    cin >> s;

    // if (s.substr(0, 3) == "xyz" || s.substr(0, 3) == "zzz") {
    //     printf("fuck\n");
    //     return 0;
    // }

    int sum = 0;
    for (char c: s) sum += c - 'a' + 1;

    int OFF = sum;
    vector<int> vp(2*OFF + 1), vm(2*OFF + 1);
    int acc = 0;
    vm[OFF] = 1;
    
    for (char c: s) {
        acc += c - 'a' + 1;
        vp[acc] = 1;
        vm[OFF - acc] = 1;
    }
    NTT(vp, 1, K, C, 3);
    for (size_t i = 0; i < vp.size(); i++)
        vp[i] = v2[i];
    NTT(vm, 1, K, C, 3);
    for (size_t i = 0; i < vp.size(); i++)
        vp[i] = vp[i] * v2[i] % P;
    NTT(vp, -1, K, C, 3);
    
    int ans = 0;
    for (int i = OFF + 1; i <= 2 * OFF; i++) {
        ans += (v2[i] % P != 0);
    }
    cout << ans << endl;
    return 0;
}
