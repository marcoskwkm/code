#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

int grid[MAXN][MAXN];
int sol[MAXN][MAXN];
int sum_row[MAXN], sum_col[MAXN];

void no_solution() {
    printf("0\n");
    exit(0);
}

int main() {
    int n;
    cin >> n;
    lint sum_all = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            scanf("%d", &grid[r][c]);
            sum_all += grid[r][c];
            sum_row[r] += grid[r][c];
            sum_col[c] += grid[r][c];
        }
    }
    if (n == 1) {
        printf("%d\n", (grid[0][0] == 0 || grid[0][0] == 1) ? 1 : 0);
        return 0;
    }
    
    if (sum_all % (2*n - 1)) no_solution();
    sum_all /= 2*n - 1;

    for (int i = 0; i < n; i++) {
        if ((sum_row[i] - sum_all) % (n - 1)) no_solution();
        if ((sum_col[i] - sum_all) % (n - 1)) no_solution();
        sum_row[i] = (sum_row[i] - sum_all) / (n - 1);
        sum_col[i] = (sum_col[i] - sum_all) / (n - 1);
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int x = sum_row[r] + sum_col[c] - grid[r][c];
            if (x != 0 && x != 1) no_solution();
        }
    }

    printf("1\n");        
    return 0;
}
