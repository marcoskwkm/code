typedef double CTYPE;

struct Point {
    CTYPE x, y, z;
    Point(CTYPE xx = 0, CTYPE yy = 0, CTYPE zz = 0) {
        x = xx, y = yy, z = zz;
    }
};

typedef Point Vector;

double norm(const Vector &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

Point operator+(const Point &p, const Vector &v) {
    return Point(p.x + v.x, p.y + v.y, p.z + v.z);
}

Vector operator-(const Point &p, const Point &q) {
    return Vector(p.x - q.x, p.y - q.y, p.z - q.z);
}

CTYPE operator*(const Vector &u, const Vector &v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

Vector operator*(CTYPE k, const Vector &v) {
    return Vector(k*v.x, k*v.y, k*v.z);
}

Vector operator^(const Vector &u, const Vector &v) {
    return Vector(u.y*v.z - u.z*v.y,
                  u.z*v.x - u.x*v.z,
                  u.x*v.y - u.y*v.x);
}

// finds Ax + By + Cz + D = 0, given three points on the plane
tuple<double, double, double, double>
get_plane_equation(const Point &p1, const Point &p2, const Point &p3) {
    Vector u = p2 - p1, v = p3 - p1;
    Vector n = u ^ v;
    return make_tuple(n.x, n.y, n.z, -n.x*p1.x - n.y*p1.y - n.z*p1.z);
}

// finds Ax + By + Cz + D = 0, given a point and a normal vector
tuple<double, double, double, double>
get_plane_equation(const Point &p, const Vector &n) {
    return make_tuple(n.x, n.y, n.z, -(p * n));
}

pair<Point, bool> get_line_plane_intersection(const Point &p1, const Point &p2,
                                              double a, double b, double c, double d) {
    Vector v = p2 - p1, n(a, b, c);
    double t = -(d + p1*n) / (v * n);
    Point p = p1 + t*v;
    bool intersects = (0 - EPS <= t && t <= 1 + EPS);
    return make_pair(p, intersects);
}

double get_point_line_dist(const Point &p, const Point &pr, const Vector &dir) {
    Vector u = p - pr;
    return norm(u ^ dir) / norm(dir);
}
