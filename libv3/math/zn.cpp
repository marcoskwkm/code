// Ring of integers modulo n
template<int mod>
struct ZN {
    int x;
    ZN() : x(0) {}
    ZN(int _x) : x((_x % mod + mod) % mod) {}
    ZN operator+(ZN that) { return ZN((x + that.x) % mod); }
    ZN operator-(ZN that) { return ZN((x - that.x + mod) % mod); }
    ZN operator*(ZN that) { return ZN((lint(x) * that.x) % mod); }
    ZN &operator+=(ZN that) { return *this = *this + that; }
    ZN &operator-=(ZN that) { return *this = *this - that; }
    ZN &operator*=(ZN that) { return *this = *this * that; }
    ZN operator-() { return ZN(-x); }
    bool operator==(ZN that) { return x == that.x; }
    bool operator!=(ZN that) { return x != that.x; }
    friend ostream &operator<<(ostream &os, ZN a) { return os << a.x; }
    friend istream &operator>>(istream &is, ZN &a) { return is >> a.x; }
};