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
