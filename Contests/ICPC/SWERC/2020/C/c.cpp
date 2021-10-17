#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

template<class T> struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    T norm2() { return x * x + y * y; }
    double norm() { return sqrt(norm2()); }
    Point<T> rotate(T alpha) {
        return Point<T>(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
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
template<class T> Vector<T> operator*(const Vector<T> &v, T k) { return k * v; }
template<class T> Vector<T> operator/(const Vector<T> &v, T k) {
    return Vector<T>(v.x / k, v.y / k);
}

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;

    Graph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v) { adj[u].push_back(v); }
};

long double X, Y;
int n;
bool seen[MAXN];

void dfs(int v, Graph &g) {
    seen[v] = 1;
    for (int nxt: g.adj[v]) {
        if (!seen[nxt]) {
            dfs(nxt, g);
        }
    }
}

bool check(vector<Point<long double>> &v, long double m) {
    Graph g(n + 4);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Vector<long double> w = v[j] - v[i];
            if (w.norm2() <= 4 * m * m) {
                g.add_edge(i, j);
                g.add_edge(j, i);
            }
        }
    }

    int u = n, d = n + 1, l = n + 2, r = n + 3;
    for (int i = 0; i < n; i++) {
        if (v[i].x <= m) {
            g.add_edge(i, l);
            g.add_edge(l, i);
        }
        if (v[i].x + m >= X) {
            g.add_edge(i, r);
            g.add_edge(r, i);
        }
        if (v[i].y <= m) {
            g.add_edge(i, d);
            g.add_edge(d, i);
        }
        if (v[i].y + m >= Y) {
            g.add_edge(i, u);
            g.add_edge(u, i);
        }
    }

    memset(seen, 0, sizeof(seen));
    dfs(l, g);
    if (seen[r] || seen[d]) {
        return 1;
    }
    memset(seen, 0, sizeof(seen));
    dfs(u, g);
    return seen[d] || seen[r];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> X >> Y >> n;

    vector<Point<long double>> v;
    for (int i = 0; i < n; i++) {
        long double x, y;
        cin >> x >> y;
        v.push_back(Point<long double>(x, y));
    }

    long double l = 0, r = X;
    for (int step = 0; step < 100; step++) {
        long double m = (l + r) / 2;
        if (check(v, m)) {
            r = m;
        } else {
            l = m;
        }
    }

    printf("%.6Lf\n", l);
    return 0;
}
