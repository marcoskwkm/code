// Returns (x, y) such that ax + by = gcd(a, b)
pll bezout(lint a, lint b) {
    if (b == 0) return pll(1, 0);
    pll p = bezout(b, a % b);
    return pll(p.second, p.first - (a / b) * p.second);
}
