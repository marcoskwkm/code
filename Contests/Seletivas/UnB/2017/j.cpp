#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXL = (int)2e5 + 10;

typedef complex<long double> Complex;
const long double PI = acos(-1.0L);

lint modexp(lint b, lint e, lint m) {
    lint ret = 1;
    while (e) {
        if (e & 1) ret = ret * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return ret;
}

vector<lint> NTT(vector<lint> v, int type, int c, int k, int r) {
    lint P = c * (1 << k) + 1;
    int n = v.size();
    while (n & (n - 1)) { v.push_back(0); n++; }
    int logn = __builtin_ctz(n);
    vector<lint> v2(n);
    for (int i = 0; i < n; i++) {
        int mask = 0;
        for (int j = 0; j < logn; j++)
            if (i & (1 << j))
                mask |= (1 << (logn - 1 - j));
        v2[mask] = v[i];
    }
    for (int len = 1, s = 1; 2 * len <= n; len <<= 1, s++) {
        lint wm = modexp(r, c * (1 << (k - s)), P);
        if (type == -1) wm = modexp(wm, P - 2, P);
        for (int i = 0; i < n; i += 2 * len) {
            lint w = 1;
            for (int j = 0; j < len; j++) {
                lint t = w * v2[i + j + len] % P;
                v2[i + j + len] = v2[i + j] - t;
                v2[i + j] = v2[i + j] + t;
                w = w * wm % P;
            }
        }
    }
    if (type == -1) {
        lint invn = modexp(n, P - 2, P);
        for (lint &x: v2) x = (x * invn) % P;
    }
    for (lint &x: v2) x = (x % P + P) % P;
    return v2;
} 

int main() {
    const int C = 13, K = 20, R = 15;
    const int P = C * (1 << K) + 1;
    string text, pattern;
    cin >> text >> pattern;
    vector<lint> t1, t2, t3, p1, p2, p3;
    for (char c: text) {
        int x = c - 'a' + 1;
        t1.push_back(x);
        t2.push_back(x*x);
        t3.push_back(x*x*x);
    }
    for (char c: pattern) {
        int x = c - 'a' + 1;
        if (c == '*') x = 0;
        p1.push_back(x);
        p2.push_back(x*x);
        p3.push_back(x*x*x);
    }
    reverse(p1.begin(), p1.end());
    reverse(p2.begin(), p2.end());
    reverse(p3.begin(), p3.end());
    int n = text.size() + pattern.size();
    t1.resize(n), t2.resize(n), t3.resize(n);
    p1.resize(n), p2.resize(n), p3.resize(n);
    t1 = NTT(t1, 1, C, K, R), t2 = NTT(t2, 1, C, K, R), t3 = NTT(t3, 1, C, K, R);
    p1 = NTT(p1, 1, C, K, R), p2 = NTT(p2, 1, C, K, R), p3 = NTT(p3, 1, C, K, R);
    vector<lint> r1, r2, r3;
    for (size_t i = 0; i < t1.size(); i++) {
        r1.push_back(t1[i] * p3[i] % P);
        r2.push_back(t2[i] * p2[i] % P);
        r3.push_back(t3[i] * p1[i] % P);
    }
    r1 = NTT(r1, -1, C, K, R), r2 = NTT(r2, -1, C, K, R), r3 = NTT(r3, -1, C, K, R);
    vector<int> ans;
    for (size_t j = 0; j + pattern.size() <= text.size(); j++) {
        size_t i = j + pattern.size() - 1;
        if (r1[i] - 2*r2[i] + r3[i] == 0) {
            ans.push_back(j + 1);
        }
    }
    if (ans.empty()) printf("-1\n");
    else {
        for (size_t i = 0; i < ans.size(); i++)
            printf("%d%c", ans[i], i + 1 == ans.size() ? '\n' : ' ');
    }
    return 0;
}
