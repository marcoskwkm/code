#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

double q[3];

int main() {
    int n;
    while (scanf("%d", &n) > 0) {
        q[0] = q[1] = q[2] = 0;
        for (int i = 0; i < n; i++) {
            double x;
            scanf("%lf", &x);
            q[i % 3] += x;
        }
        printf("Junior: R$%.2f\n", q[1] + q[2]);
        printf("Thiago: R$%.2f\n", q[0]);
    }        
    return 0;
}
