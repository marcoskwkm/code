#include <bits/stdc++.h>
using namespace std;

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
    int N = 10, T = 100;
    printf("%d\n", T);

    Random rng;

    for (int t = 1; t <= T; t++) {
        printf("%d\n", N);

        rng.initialize_uniform_int(1, 1000);
        for (int i = 0; i < N; i++) {
            printf("%d ", rng.get_rand_int());
        }
        printf("\n");

        for (int i = 0; i < N; i++) {
            rng.initialize_uniform_int(0, i);
            printf("%d ", rng.get_rand_int());
        }
        printf("\n");
    }

    return 0;
}
