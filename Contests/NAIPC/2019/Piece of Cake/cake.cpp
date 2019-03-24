#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2510;

template<class T> struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    T norm2() { return x * x + y * y; }
    double norm() { return sqrt(norm2()); }
    Point<T> rotate(T alpha) {
        return Point<T>(x * cos(alpha) - y * sin(alpha),
                        x * sin(alpha) + y * cos(alpha));
    }
    double arg() { return atan2(y, x); } // [-PI, PI]
};
template<class T> using Vector = Point<T>;
template<class T> using Poly = vector<Point<T>>;

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

// choose(n1, k1) / choose(n2, k2)
long double getProb(int n1, int k1, int n2, int k2) {
    k1 = min(k1, n1 - k1);
    k2 = min(k2, n2 - k2);
    vector<int> nums, dens;
    for (int i = 0; i < k1; i++) {
        nums.push_back(n1 - i);
        dens.push_back(k1 - i);
    }
    for (int i = 0; i < k2; i++) {
        nums.push_back(k2 - i);
        dens.push_back(n2 - i);
    }
    
    long double ret = 1;
    for (int den: dens) {
        while (ret <= 1 && !nums.empty()) {
            ret *= nums.back();
            nums.pop_back();
        }
        ret /= den;
    }
    for (int num: nums) ret *= num;
    return ret;
}
    
// signedArea is positive iff points are in ccw order
template<class T> T signedArea(const Poly<T> &poly) {
    int n = poly.size();
    T ret = 0;
    for (int i = 0; i < n; i++) {
        int j = (i == n - 1 ? 0 : i + 1);
        ret += poly[i] ^ poly[j];
    }
    return ret / 2;
}

template<class T> T area(const Poly<T> &poly) { return fabs(signedArea(poly)); }

int main() {
    int n, k;
    cin >> n >> k;

    long double prob = getProb(n - 2, k - 2, n, k);
    
    Poly<long double> poly;
    for (int i = 0; i < n; i++) {
        Point<long double> p;
        scanf("%Lf%Lf", &p.x, &p.y);
        poly.push_back(p);
    }
    long double ans = 0;
    for (int p = 0; p < n; p++) {
        long double area = 0;
        long double curProb = prob;
        int rem = n - 2;
        for (int q = (p + 1) % n; q != p; q = (q + 1) % n) {
            ans += curProb * area;
            curProb = curProb * (rem - (k - 2)) / rem;            
            int r = (q + 1) % n;
            area += (poly[r] - poly[p]) ^ (poly[q] - poly[p]);
            rem--;
            if (rem < k - 2) break;
        }
    }

    printf("%.8Lf\n", area(poly) - ans / 2);
    return 0;
}
