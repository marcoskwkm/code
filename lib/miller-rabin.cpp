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

    // O(log^2 n), works for any n < 2^64
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
