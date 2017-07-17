#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const long double PI = acos(-1.0L);
const long double EPS = 1e-6;

int main() {
    long double da, db, dc;
    while (cin >> da >> db >> dc) {
        long double l = 0, r = 1e9;
        l = max(fabs(da - db), max(fabs(da - dc), fabs(db - dc)));
        r = min(da + db, min(da + dc, db + dc));
        if (l > r) {
            printf("-1.000\n");
            continue;
        }
        long double angle_a, angle_b, angle_c;
        long double cos_c, cos_b, cos_a;
        for (int s = 0; s < 200; s++) {
            long double m = (l + r) / 2;
            cos_c = (da*da + db*db - m*m) / (2*da*db);
            cos_b = (da*da + dc*dc - m*m) / (2*da*dc);
            cos_a = (db*db + dc*dc - m*m) / (2*db*dc);
            angle_c = acos(cos_c);
            angle_b = acos(cos_b);
            angle_a = acos(cos_a);
            if (angle_a + angle_b + angle_c < 2*PI)
                l = m;
            else
                r = m;
        }
        if (fabs(angle_a + angle_b + angle_c - 2*PI) < EPS)
            printf("%.3Lf\n", l*l * sqrt(3.0L) / 4);
        else
            printf("-1.000\n");
    }        
    return 0;
}
