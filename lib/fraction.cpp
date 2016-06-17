template<class T> class Fraction {
    static T gcd(T a, T b) {
        while (b) {
            T na = b, nb = a % b;
            a = na, b = nb;
        }
        return a;
    }
    
public:
    T num, den;
    
    Fraction(T a = 0, T b = 1) {
        T d = gcd(a, b);
        a /= d, b /= d;
        if (b < 0) a *= -1, b *= -1;
        num = a, den = b;
    }

    Fraction<T> operator+ (const Fraction<T> &that) const {
        return Fraction(num * that.den + that.num * den, den * that.den);
    }

    Fraction<T> operator- (const Fraction<T> &that) const {
        return Fraction(num * that.den - that.num * den, den * that.den);
    }

    Fraction<T> operator* (const Fraction<T> &that) const {
        return Fraction(num * that.num, den * that.den);
    }

    Fraction<T> operator/ (const Fraction<T> &that) const {
        return Fraction(num * that.den, den * that.num);
    }

    Fraction<T> operator* (const T &that) const {
        return Fraction(num * that, den);
    }

    Fraction<T> operator/ (const T &that) const {
        return Fraction(num, that * den);
    }

    bool operator< (const Fraction<T> &that) const {
        return num * that.den < that.num * den;
    }

    bool operator> (const Fraction<T> &that) const {
        return num * that.den > that.num * den;
    }

    bool operator== (const Fraction<T> &that) const {
        return num == that.num && den == that.den;
    }

    bool operator!= (const Fraction<T> &that) const {
        return !(*this == that);
    }
};
