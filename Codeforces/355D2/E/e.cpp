#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;
const int MOD = (int)1e9 + 7;

int grid[MAXN][MAXN];
// dl, d, dr, r
int prvr[] = {-1, -1, -1, 0};
int prvc[] = {1, 0, -1, -1};
int acc0[4][MAXN][MAXN];
long double acclog[4][MAXN][MAXN];
lint accprod[4][MAXN][MAXN];
lint invprod[4][MAXN][MAXN];

const int inv[] = {0, 1, 500000004, 333333336};

int main() {
    int n;
    scanf("%d", &n);
    char buff[MAXN];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            accprod[j][0][i] = accprod[j][i][0] = 1;
            invprod[j][0][i] = invprod[j][i][0] = 1;
            accprod[j][n + 1][i] = accprod[j][i][n + 1] = 1;
            invprod[j][n + 1][i] = invprod[j][i][n + 1] = 1;
        }
    }
    for (int r = 1; r <= n; r++) {
        scanf("%s", buff);
        for (int c = 1; c <= n; c++) {
            grid[r][c] = buff[c - 1] - '0';
            for (int i = 0; i < 4; i++) {
                int pr = r + prvr[i], pc = c + prvc[i];
                acc0[i][r][c] = acc0[i][pr][pc] + (grid[r][c] == 0);
                if (grid[r][c]) acclog[i][r][c] = acclog[i][pr][pc] + log(grid[r][c]);
                else acclog[i][r][c] = 0;
                accprod[i][r][c] = (accprod[i][pr][pc] * max(1, grid[r][c])) % MOD;                
                invprod[i][r][c] = (invprod[i][pr][pc] * inv[max(1, grid[r][c])]) % MOD;
            }
        }
    }
    long double best = -1;
    int ans = 0;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (grid[r][c] == 0) continue;
            // +
            int ll = 0, rr = n;
            while (ll < rr) {
                int mid = (ll + rr + 1) / 2;
                if (r - mid <= 0 || c - mid <= 0 || r + mid > n || c + mid > n) rr = mid - 1;
                else if (acc0[1][r + mid][c] - acc0[1][r - mid - 1][c] +
                         acc0[3][r][c + mid] - acc0[3][r][c - mid - 1] > 0)
                    rr = mid - 1;
                else ll = mid;
            }
            double got = acclog[1][r + ll][c] - acclog[1][r - ll - 1][c] +
                acclog[3][r][c + ll] - acclog[3][r][c - ll - 1] - log(grid[r][c]);
            if (got > best) {
                best = got;
                lint prodmod1 = (accprod[1][r + ll][c] * invprod[1][r - ll - 1][c]) % MOD;
                lint prodmod2 = (accprod[3][r][c + ll] * invprod[3][r][c - ll - 1]) % MOD;
                ans = (prodmod1 * prodmod2) % MOD * inv[grid[r][c]] % MOD;
            }

            // x
            ll = 0, rr = n;
            while (ll < rr) {
                int mid = (ll + rr + 1) / 2;
                if (r - mid <= 0 || c - mid <= 0 || r + mid > n || c + mid > n) rr = mid - 1;
                else if (acc0[0][r + mid][c - mid] - acc0[0][r - mid - 1][c + mid + 1] +
                         acc0[2][r + mid][c + mid] - acc0[2][r - mid - 1][c - mid - 1] > 0)
                    rr = mid - 1;
                else ll = mid;
            }
            got = acclog[0][r + ll][c - ll] - acclog[0][r - ll - 1][c + ll + 1] +
                acclog[2][r + ll][c + ll] - acclog[2][r - ll - 1][c - ll - 1] - log(grid[r][c]);
            if (got > best) {                
                best = got;
                lint prodmod1 = (accprod[0][r + ll][c - ll] * invprod[0][r - ll - 1][c + ll + 1]) % MOD;
                lint prodmod2 = (accprod[2][r + ll][c + ll] * invprod[2][r - ll - 1][c - ll - 1]) % MOD;
                ans = (prodmod1 * prodmod2) % MOD * inv[grid[r][c]] % MOD;
            }            
        }
    }
    printf("%d\n", ans);        
    return 0;
}
