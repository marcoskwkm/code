#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef complex<long double> Complex;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const long double PI = acos(-1.0L);
const double EPS = 1e-12;

int main() {
    Complex pos(0);
    Complex curdir(0, 1);
    string foo;
    long double deg, angle, length;
    int n;
    Complex ONE(1, 0), I(0, 1);
    while (cin >> foo) {
        cin >> deg >> foo >> length >> foo >> n;
        angle = deg * PI / 180;
        Complex rot = polar<long double>(1, -angle);
        Complex add = curdir * length * rot;
        Complex finaldir = polar<long double>(1, -angle * n);
        if (deg == 0 || deg == 360) {
            add *= n;
        }
        else {
            add *= (finaldir - ONE) / (rot - ONE);
        }
        pos += add;
        curdir *= finaldir;
    }
    double x = EPS + pos.real();
    double y = EPS + pos.imag();
//    cout << fixed << setprecision(2) << -pos.real() + EPS << " " <<  pos.imag() + EPS << endl;
    printf("%.2f %.2f\n", x, y);
    return 0;
}
