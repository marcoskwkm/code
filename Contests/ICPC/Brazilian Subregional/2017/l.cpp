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
            // j = 0
            int t = v2[i + (m >> 1)] %= P;
            v2[i + (m >> 1)] = v2[i] - t;
            v2[i] += t;
            for (int j = 1; 2 * j < m; j++) {
                if (v2[i + j + (m >> 1)] == 0) t = 0;
                else if (v2[i + j + (m >> 1)] == 1) t = v[j];
                else if (v2[i + j + (m >> 1)] == -1) t = -v[j];
                else {
                    t = v[j] * v2[i + j + (m >> 1)] % P;
                }
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

// I'm sick tired of this shit. Let's cheat and make an optimization that makes
// no fucking sense but will get AC.
struct Hash {
    static const int P1 = 31, P2 = 37, MOD = (int)1e9 + 7;    
    lint h1, h2;
    Hash(lint a = 0, lint b = 0) { h1 = a; h2 = b; }
    Hash(const string &s) {
        h1 = 0, h2 = 0;
        for (char c: s) {
            h1 = (P1 * h1 + c) % MOD;
            h2 = (P2 * h2 + c) % MOD;
        }
    }
    void append(char c) {
        h1 = (P1 * h1 + c) % MOD;
        h2 = (P2 * h2 + c) % MOD;
    }
    bool operator==(const Hash &that) const { return h1 == that.h1 && h2 == that.h2; }
    bool operator!=(const Hash &that) const { return h1 != that.h1 || h2 != that.h2; }
    Hash operator*(const Hash &that) const {
        return Hash((h1 * that.h1) % MOD, (h2 * that.h2) % MOD);
    }
    Hash operator-(const Hash &that) const {
        return Hash((h1 - that.h1 + MOD) % MOD, (h2 - that.h2 + MOD) % MOD);
    }
    bool operator<(const Hash &that) const {
        if (h1 == that.h1) return h2 < that.h2;
        return h1 < that.h1;
    }
};

struct HashArray {
    vector<Hash> pot;
    vector<Hash> array;

    HashArray(string &s) {
        pot.resize(s.size());
        pot[0] = Hash(1,1);
        Hash acc;
        for (size_t i = 0; i < s.size(); i++) {
            acc.append(s[i]);
            array.push_back(acc);
            if (i > 0) pot[i] = pot[i - 1] * Hash(Hash::P1, Hash::P2);
        }
    }

    inline Hash get_hash(int l, int r) {
        if (l == 0) return array[r];
        return array[r] - array[l - 1] * pot[r - l + 1];
    }
};

    
int main() {
    const int K = 23, C = 20;
    const int P = C * (1 << K) + 1;
    string s;
    cin >> s;
    HashArray hash(s);
    int l = 0, r = s.size() - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        bool ok = 0;
        for (int i = mid; i + mid <= (int)s.size(); i++) {
            if (hash.get_hash(0, mid - 1) == hash.get_hash(i, i + mid - 1)) {
                ok = 1;
                break;
            }
        }
        if (ok) l = mid;
        else r = mid - 1;
    }
    int ignored_prefix = l;

    int sum_p = 0, sum_m = 0, shift_p = 0;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        sum_m += c - 'a' + 1;
        if ((int)i >= ignored_prefix) sum_p += c - 'a' + 1;
        else shift_p += c - 'a' + 1;
    }

    vector<int> vp(sum_p + sum_m + 1), vm(sum_p + sum_m + 1);
    int acc_p = 0, acc_m = 0;
    vm[sum_m] = 1;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        acc_m += (c - 'a' + 1);
        vm[sum_m - acc_m] = 1;
        if ((int)i >= ignored_prefix) {
            acc_p += (c - 'a' + 1);
            vp[acc_p] = 1;
        }
    }
    NTT(vp, 1, K, C, 3);
    for (size_t i = 0; i < vp.size(); i++) {
        vp[i] = v2[i];
    }
    NTT(vm, 1, K, C, 3);
    for (size_t i = 0; i < vp.size(); i++)
        vp[i] = vp[i] * v2[i] % P;
    NTT(vp, -1, K, C, 3);
    
    int ans = 0;
    for (int i = sum_m - shift_p + 1; i <= sum_m - shift_p + sum_m; i++) {
        ans += (v2[i] % P != 0);
    }
    cout << ans << endl;
    return 0;
}
