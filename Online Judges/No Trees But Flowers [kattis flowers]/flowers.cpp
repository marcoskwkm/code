#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int NINTS = (int)1e6 + 10;
const double PI = acos(-1.0);

// Uses Simpson's rule to integrate f from x0 to x1 using 2*n subintervals
double integrate(function<double(double)> f, double x0, double x1, int n) {
    n *= 2; // n must be even
    double h = (x1 - x0) / n;
    double sum = f(x0) + f(x1);
    for (int i = 1; 2*i <= n; i++) {
        if (2*i < n) sum += 2*f(x0 + 2*i*h);
        sum += 4*f(x0 + (2*i - 1)*h);
    }
    return sum * h / 3;
}    

int main() {
    double v;
    int n;
    scanf("%lf%d", &v, &n);
    int ans = -1;
    double best_fit = INF;
    for (int i = 0; i < n; i++) {
        double a, b, h;
        scanf("%lf%lf%lf", &a, &b, &h);
        function<double(double)> f = [=](double x) { return a*exp(-x*x) + b*sqrt(x); };
        function<double(double)> f2 = [=](double x) { double y = f(x); return y*y; };
        double vol = PI * integrate(f2, 0, h, NINTS);
        if (fabs(v - vol) < best_fit) {
            best_fit = fabs(v - vol);
            ans = i;
        }
    }
    printf("%d\n", ans);        
    return 0;
}
