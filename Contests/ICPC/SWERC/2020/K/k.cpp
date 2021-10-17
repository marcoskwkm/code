#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

struct Hash {
    static const int P1 = 31;
    int h1;

    Hash(int a = 0) { h1 = a; }
    Hash(const string &s) {
        h1 = 0;
        for (char c: s) {
            h1 = P1 * h1 + c;
        }
    }
    void append(char c) { h1 = P1 * h1 + c; }
    bool operator==(const Hash &that) const { return h1 == that.h1; }
    bool operator!=(const Hash &that) const { return h1 != that.h1; }
    Hash operator*(const Hash &that) const { return Hash(h1 * that.h1); }
    Hash operator-(const Hash &that) const { return Hash(h1 - that.h1); }
    bool operator<(const Hash &that) const { return h1 < that.h1; }
};

struct HashArray {
    vector<Hash> pot;
    vector<Hash> array;

    HashArray(string &s) {
        pot.resize(s.size());
        pot[0] = Hash(1);
        Hash acc;
        for (size_t i = 0; i < s.size(); i++) {
            acc.append(s[i]);
            array.push_back(acc);
            if (i > 0)
                pot[i] = pot[i - 1] * Hash(Hash::P1);
        }
    }

    inline Hash get_hash(int l, int r) {
        if (l == 0)
            return array[r];
        return array[r] - array[l - 1] * pot[r - l + 1];
    }
};

const int MAXN = 310000;
int v[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    HashArray hash(s);

    int l = 1, r = s.size();
    while (l < r) {
        int m = (l + r) / 2;
        bool ok = 0;
        int len = 0;
        for (int i = 0; i + m - 1 < (int)s.size(); i++) {
            Hash h = hash.get_hash(i, i + m - 1);
            v[i] = h.h1;
            len++;
        }
        sort(v, v + len);
        for (int i = 0; i < len; i++) {
            if (i + 1 == len || v[i + 1] != v[i]) {
                ok = 1;
            }
            while (i + 1 < len && v[i] == v[i + 1])
                i++;
        }

        if (ok) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    map<int, int> f;
    for (int i = 0; i + l - 1 < (int)s.size(); i++) {
        Hash h = hash.get_hash(i, i + l - 1);
        f[h.h1]++;
    }
    for (int i = 0; i + l - 1 < (int)s.size(); i++) {
        Hash h = hash.get_hash(i, i + l - 1);
        if (f[h.h1] == 1) {
            printf("%s\n", s.substr(i, l).c_str());
            return 0;
        }
    }

    return 0;
}
