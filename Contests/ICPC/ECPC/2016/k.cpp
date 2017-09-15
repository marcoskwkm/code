#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 22;

long double P[MAXN][MAXN], C[MAXN][MAXN];
int seq[MAXN];

long double p1[MAXN][MAXN];
long double p2[MAXN][MAXN];

int main() {
    #ifndef HOME
    freopen("trip.in", "r", stdin);
    #endif

    int t;
    for (scanf("%d", &t); t--;) {
        int n, m, k, q, z;
        scanf("%d%d%d%d%d", &n, &m, &k, &q, &z);
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                cin >> P[r][c];
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                cin >> C[r][c];
        for (int i = 0; i < k; i++)
            scanf("%d", &seq[i]);

        memset(p1, 0, sizeof(p1));
        p1[0][0] = C[0][seq[0]];
        for (int i = 0; i + 1 < k; i++)
            for (int j = 0; j < n; j++)
                for (int l = 0; l < n; l++)
                    p1[i + 1][l] += p1[i][j] * P[j][l] * C[l][seq[i + 1]];
        long double sum = 0;
        for (int i = 0; i < n; i++)
            sum += p1[k - 1][i];
        if (sum == 0) printf("0.000\n");
        else printf("%.3f\n", double(p1[k - 1][z] / sum));
    }        
    return 0;
}
