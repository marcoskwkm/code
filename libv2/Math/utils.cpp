// Computes b ^ e (mod m)
lint modexp(lint b, lint e, lint m) {
    lint ret = 1;
    while (e) {
        if (e & 1) ret = (ret * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return (ret % m + m) % m;
}
