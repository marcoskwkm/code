#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

lint find_sol(lint a, lint b, lint c) {
    if (a == 0) {
        if ((-c) % b) return -1;
        return (-c / b);
    }
    long double delta = double(b * b) - double(4) * a * c;
    if (delta < 0) return -1;
    long double root = (-b + sqrt(delta)) / 2 / a;
    lint x = root - 1;
    for (int i = 0; i < 2; i++, x++) {
        if (a*x*x + b*x + c == 0) return x;
    }
    return -1;    
}

int main() {
    lint y, l;
    scanf("%lld%lld", &y, &l);
    lint ans = 0;
    for (int b = 1000000; b >= 2; b--) {
        string rep = "";
        lint yy = y;
        bool ok = 1;
        while (yy) {
            lint d = yy % b;
            yy /= b;
            if (d > 9) ok = 0;
            rep = rep + char(d + '0');
        }
        int len = rep.size();
        lint x = 0;
        for (int i = len - 1; i >= 0; i--) {
            x = 10*x + rep[i] - '0';
        }
        if (x < l) continue;
        if (ok) {
            ans = max<lint>(ans, b);
        }
    } 
    for (int a = 0; a <= 9; a++) {
        for (int c = 0; c <= 9; c++) {
            for (int d = 0; d <= 9; d++) {
                if (100 * a + 10*c  + d < l) continue;
                lint sol = find_sol(a, c, d - y);
                ans = max(ans, sol);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
