#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 12;

double p[MAXN][MAXN];
int v[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &p[i][j]);
    for (int i = 0; i < n; i++)
        v[i] = i;
    double ans = 0;
    do {
        double prob = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (v[i] < v[j]) prob *= p[i][j];
                else prob *= p[j][i];
            }
        }
        ans += prob;
    } while (next_permutation(v, v + n));

    printf("%.15f\n", ans);        
    return 0;
}
