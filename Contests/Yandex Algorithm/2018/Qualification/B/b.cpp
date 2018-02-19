// AC

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int seq[2 * MAXN][MAXN];
bool is_first[MAXN * MAXN];
int mat[MAXN][MAXN];

int main() {
    int n;
    cin >> n;
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    fill(is_first, is_first + MAXN*MAXN, 1);
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &seq[i][j]);
            if (j) is_first[seq[i][j]] = 0;
        }
    }

    int first_elem = -1;
    for (int i = 1; i <= n * n; i++) {
        if (is_first[i]) {
            assert(first_elem == -1);
            first_elem = i;
        }
    }
    mat[0][0] = first_elem;
    
    for (int i = 0; i < 2 * n; i++) {
        if (seq[i][0] != first_elem) continue;
        if (mat[0][1] == 0)
            for (int j = 1; j < n; j++)
                mat[0][j] = seq[i][j];
        else
            for (int j = 1; j < n; j++)
                mat[j][0] = seq[i][j];
    }
    assert(mat[0][1] != 0 && mat[1][0] != 0);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (seq[j][0] != mat[0][i]) continue;
            for (int k = 1; k < n; k++)
                mat[k][i] = seq[j][k];
            break;
        }
    }

    for (int i = 0; i < n * n; i++)
        printf("%d%c", mat[i / n][i % n], (i + 1 == n * n) ? '\n' : ' ');
    
    return 0;
}
