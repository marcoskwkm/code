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
