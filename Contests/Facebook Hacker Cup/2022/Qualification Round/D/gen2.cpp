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
    int T = 70;
    printf("%d\n", T);
    int cs = 630;
    for (int t = 1; t <= T; t++) {
        int n = cs, m = cs * (cs - 1) / 2, q = m;

        Random rng, rng2;
        rng.initialize_uniform_int(1, n);
        rng2.initialize_uniform_int(1, 1000000000);

        printf("%d %d %d\n", n, m, q);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                printf("%d %d %d\n", i + 1, j + 1, rng2.get_rand_int());
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // printf("%d %d\n", i + 1, j + 1);
                printf("%d %d\n", 1, 2);
            }
        }
    }
}
