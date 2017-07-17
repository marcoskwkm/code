#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2010;

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
template<class T> using Poly = vector<Point<T>>;

template<class T> Point<T> operator-(const Point<T> &p, const Point<T> &q) {
    return Point<T>(p.x - q.x, p.y - q.y);
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

// Checks whether c1 is strictly inside c2
template<class T> bool is_inside(const Circle<T> &c1, const Circle<T> &c2) {
    if (c1.r >= c2.r) return 0;
    T d2 = (c2.o - c1.o).norm2();
    return d2 < (c2.r - c1.r) * (c2.r - c1.r);
}

vector<int> adj[MAXN];
int qa[MAXN], qb[MAXN];
int bestq[MAXN][MAXN];
int energy[MAXN][MAXN];
int next_best[MAXN][MAXN];
int min_ancestors[MAXN];
int n_ancestors[MAXN];
bool done[MAXN];
bool can_take[MAXN];

lint dfs(int v, int q) {
    n_ancestors[v] = q;
    lint ret = bestq[v][q];
    for (int nxt: adj[v])
        ret += dfs(nxt, q + 1);
    return ret;
}

bool dfs2(int v, int depth, int n_inactive) {
    // printf("dfs2(%d, %d, %d), min = %d\n", v, depth, n_inactive, min_ancestors[v]);
    if (done[v] || energy[v][n_inactive] != bestq[v][n_ancestors[v]])
        can_take[v] = 0;
    int ret = 0;
    if (n_inactive == min_ancestors[v] && !done[v]) ret = 1;
    for (int nxt: adj[v]) {
        if (dfs2(nxt, depth + 1, n_inactive + 1 - done[v])) {
            ret = 1;
            can_take[v] = 0;
        }
    }
    return ret;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        scanf("%d", &n);
        vector<Circle<lint>> vc;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            int x, y, r, a, b;
            scanf("%d%d%d%d%d", &x, &y, &r, &a, &b);
            vc.push_back(Circle<lint>(x, y, r));
            qa[i] = a, qb[i] = b;
        }
        vector<int> roots;
        for (int i = 0; i < n; i++) {
            int r = INF, prv = -1;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (vc[j].r < r && is_inside(vc[i], vc[j])) {
                    r = vc[j].r;
                    prv = j;
                }
            }
            if (prv == -1) roots.push_back(i);
            else adj[prv].push_back(i);
        }

        for (int i = 0; i < n; i++) {
            int best = 0;
            for (int j = 1; j < n; j++) {
                energy[i][j] = energy[i][j - 1] + ((j & 1) ? qa[i] : qb[i]);
                best = max(best, energy[i][j]);
                bestq[i][j] = best;
            }
        }

        lint ans = 0;
        for (int root: roots)
            ans += dfs(root, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (energy[i][j] == bestq[i][n_ancestors[i]]) {
                    min_ancestors[i] = j;
                    break;
                }
            }
        }                

        memset(done, 0, sizeof(done));
        vector<int> sol;
        for (int i = 0; i < n; i++) {
            fill(can_take, can_take + n, 1);
            for (int root: roots) dfs2(root, 0, 0);            
            for (int j = 0; j < n; j++) {
                if (can_take[j]) {
                    sol.push_back(j + 1);
                    done[j] = 1;
                    break;
                }
            }
            // printf("i = %d:", i);
            // for (int j = 0; j < n; j++) printf(" %d", can_take[j]);
            // printf("\n");
        }
        assert((int)sol.size() == n);
        cout << ans << endl;
        for (int i = 0; i < n; i++)
            printf("%d%c", sol[i], i + 1 == n ? '\n' : ' ');
    }        
    return 0;
}
