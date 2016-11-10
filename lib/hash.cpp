typedef char HType;

const int P1 = 31, P2 = 37, MOD = (int)1e9 + 7;

struct Hash {
    ll h1, h2;
    Hash(ll a = 0, ll b = 0) { h1 = a; h2 = b; }
    void append(HType c) {
        h1 = (P1*h1 + c) % MOD;
        h2 = (P2*h2 + c) % MOD;
    }
    bool operator== (Hash that) const { return h1 == that.h1 && h2 == that.h2; }
    bool operator!= (Hash that) const { return h1 != that.h1 || h2 != that.h2; }
    Hash operator*  (Hash that) const {
        return Hash((h1*that.h1)%MOD, (h2*that.h2)%MOD);
    }
    Hash operator-  (Hash that) const {
        return Hash( (h1 - that.h1 + MOD)%MOD, (h2 - that.h2 + MOD)%MOD);
    }
};

Hash pot[MAXN];

vector<Hash> build_hash(int n, HType *v) {
    pot[0] = Hash(1,1);
    vector<Hash> ret;
    Hash acc;
    for (int i = 0; i < n; i++) {
        acc.append(v[i]);
        ret.push_back(acc);
        if (i > 0) pot[i] = pot[i-1] * Hash(P1, P2);
    }
    return ret;
}

inline Hash get_hash(int l, int r, vector<Hash> &hashv) {
    if (l == 0) return hashv[r];
    return hashv[r] - hashv[l-1] * pot[r-l+1];
}
