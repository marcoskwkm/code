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

    template <class I> void shuffle(I begin, I end) { std::shuffle(begin, end, rng); }
};
