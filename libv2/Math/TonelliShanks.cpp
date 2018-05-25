// Returns x such that x^2 = n (mod p), p odd prime
// Very fast, better than O(log^2(p)) on average
lint TonelliShanks(lint n, lint p) {
    n = (n % p + p) % p;
    lint Q = p - 1, S = 0;
    while ((Q & 1) == 0) {
        Q >>= 1;
        S++;
    }
    default_random_engine generator;
    uniform_int_distribution<lint> rng(1, p - 1);
    lint z = rng(generator);
    while (modexp(z, (p - 1) / 2, p) == 1) // runs 2 times on average
        z = rng(generator);
    lint c = modexp(z, Q, p), R = modexp(n, (Q + 1) / 2, p), t = modexp(n, Q, p), M = S;
    while (t != 1) {
        lint tt = t;
        int i = 0;
        while (tt != 1) {
            tt = (tt * tt) % p;
            i++;
        }
        lint b = modexp(c, (1 << (M - i - 1)), p);
        R = R * b % p, t = t * b % p * b % p, c = (b * b) % p, M = i;
    }
    return R;
}
