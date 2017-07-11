template<class T> struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    T norm2() { return x * x + y * y; }
    T norm() { return sqrt(norm2()); }
    Point<T> rotate(T alpha) {
        return Point<T>(x * cos(alpha) - y * sin(alpha),
                        x * sin(alpha) + y * cos(alpha));
    }
    T arg() { return atan2(y, x); } // [-PI, PI]
};
template<class T> using Vector = Point<T>;

template<class T> Point<T> operator-(const Point<T> &p, const Point<T> &q) {
    return Point<T>(p.x - q.x, p.y - q.y);
}
template<class T> Point<T> operator+(const Point<T> &p, const Point<T> &q) {
    return Point<T>(p.x + q.x, p.y + q.y);
}
template<class T> T operator*(const Vector<T> &u, const Vector<T> &v) {
    return u.x * v.x + u.y * v.y;
}
template<class T> T operator^(const Vector<T> &u, const Vector<T> &v) {
    return u.x * v.y - u.y * v.x;
}
template<class T> Vector<T> operator*(T k, const Vector<T> &v) {
    return Vector<T>(v.x * k, v.y * k);
}
template<class T> Vector<T> operator*(const Vector<T> &v, T k) {
    return k * v;
}
template<class T> Vector<T> operator/(const Vector<T> &v, T k) {
    return Vector<T>(v.x / k, v.y / k);
}

template<class T> struct Circle {
    Point<T> o;
    T r;
    Circle(T _x = 0, T _y = 0, T _r = 0) : o(_x, _y), r(_r) {}
    Circle(Point<T> _o, T _r) : o(_o), r(_r) {}    
};

// Assumes there are two intersection points
// Intersection arc goes from first point to second counter-clockwise
// with respect to c1
template<class T> pair<Point<T>, Point<T>> get_intersection(
    const Circle<T> &c1, const Circle<T> &c2) {
    Vector<T> vd = c2.o - c1.o;
    T d = vd.norm();
    T alpha = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Vector<T> vr = vd / d * c1.r;
    return make_pair(c1.o + vr.rotate(-alpha), c1.o + vr.rotate(+alpha));
}
