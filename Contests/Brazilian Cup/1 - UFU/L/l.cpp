#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double PI = 3.14169;
const double g = 9.80665;

int main() {
    double r, c;
    cin >> r >> c;
    double d = hypot(r, c);
    printf("%.10f\n", sqrt(PI * d / g));
    return 0;
}
