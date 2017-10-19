/*
  Number Theoretic Transform - O(N*logN)
  Performs FFT modulo prime P = c * 2^k + 1.
  k must be strictly greater than ceil(logN).
  r is a primitive root of P: it satisfies r^((P - 1) / f) != 1 (mod P),
  for every prime factor f of P - 1.
*/
  
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
