#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct Random {
    mt19937 rng;
    uniform_int_distribution<int> uniform_int;
    uniform_real_distribution<double> uniform_double;

    Random() : rng(chrono::steady_clock::now().time_since_epoch().count()) {}

    // [l, r]
    void initialize_uniform_int(int l, int r) { uniform_int = uniform_int_distribution<int>(l, r); }

    // [l, r)
    void initialize_uniform_double(double l, double r) {
        uniform_double = uniform_real_distribution<double>(l, r);
    }

    int get_rand_int() { return uniform_int(rng); }

    double get_rand_double() { return uniform_double(rng); }

    template<class I> void shuffle(I begin, I end) { std::shuffle(begin, end, rng); }
};

int main() {
    int T = 5000000 / 200000;
    printf("%d\n", T);
    for (int t = 1; t <= T; t++) {
        int n = 200000, m = 200000, q = 200000;

        Random rng, rng2;
        rng.initialize_uniform_int(1, n);
        rng2.initialize_uniform_int(1, 1000000000);

        auto gen_pair = [&]() {
            int u = rng.get_rand_int();
            while (1) {
                int v = rng.get_rand_int();
                if (u != v) {
                    return u < v ? pii(u, v) : pii(v, u);
                }
            }
        };

        printf("%d %d %d\n", n, m, q);

        set<pii> seen;

        for (int i = 0; i < m; i++) {
            pii p = gen_pair();
            while (seen.find(p) != seen.end()) {
                p = gen_pair();
            }
            printf("%d %d %d\n", p.first, p.second, rng2.get_rand_int());
        }

        for (int i = 0; i < q; i++) {
            pii p = gen_pair();
            printf("%d %d\n", p.first, p.second);
        }
    }
}
