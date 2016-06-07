#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 3600;
const double PI = acos(-1.0);
const double EPS = 1e-12;

int main() {
    double x = 0, y = 0;
    double dx = 0, dy = 1;
    string line;
    while (getline(cin, line)) {
        for (char &c: line)
            if (!isdigit(c))
                c = ' ';
        stringstream ss(line);
        int d1, d2;
        int length, rep;
//        debug("line = %s\n", line.c_str());
        ss >> d1 >> d2 >> length >> rep;
        int deg = d1*10 + d2;
        if (deg == 0 || deg == MAXD) {
            length *= rep;
            x += dx * length, y += dy * length;
        }
        else {
            int gcd = __gcd(deg, MAXD);
//            debug("gcd(%d, %d) = %d\n", deg, MAXD, gcd);
            int cycle_length = MAXD / gcd;
//            printf("cycle_length = %d\n", cycle_length);
            rep %= cycle_length;
            double seno = sin(deg * PI / 1800), cosseno = cos(deg * PI / 1800);
            for (int i = 0; i < rep; i++) {
                double ndx = dx*cosseno + dy*seno;
                double ndy = dy*cosseno - dx*seno;
                dx = ndx, dy = ndy;
                x += dx * length, y += dy * length;
            }
        }
    }
    printf("%.2f %.2f\n", x + EPS, y + EPS);        
    return 0;
}
