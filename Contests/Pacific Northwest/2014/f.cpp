#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXS = 256;
const int MOD = (int)1e9 + 9;

int n, m;
int get_mask(int m1, int m2) { return (m1 << n) | m2; }

lint mat[MAXS][MAXS];
lint res[MAXS][MAXS];

lint aux[MAXS][MAXS];
void multiply(lint m1[MAXS][MAXS], lint m2[MAXS][MAXS]) {
    memset(aux, 0, sizeof(aux));
    for (int i = 0; i < (1 << (2*n)); i++) {
	for (int j = 0; j < (1 << (2*n)); j++) {
	    for (int k = 0; k < (1 << (2*n)); k++) {
		aux[i][j] += m1[i][k] * m2[k][j];
		aux[i][j] %= MOD;
	    }
	}
    }
    memcpy(m1, aux, sizeof(aux));
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
	memset(mat, 0, sizeof(mat));
	scanf("%d%d", &n, &m);
	for (int m1 = 0; m1 < (1 << n); m1++) {
	    for (int m2 = 0; m2 < (1 << n); m2++) {
		int mask = get_mask(m1, m2);
		for (int knight_mask = 0; knight_mask < (1 << n); knight_mask++) {
		    if (knight_mask & m1) continue;
		    int nxtm1 = m2, nxtm2 = 0;
		    for (int i = 0; i < n; i++) {
			if (knight_mask & (1 << i)) {
			    if (i - 2 >= 0) nxtm1 |= (1 << (i - 2));
			    if (i - 1 >= 0) nxtm2 |= (1 << (i - 1));
			    if (i + 1 < n) nxtm2 |= (1 << (i + 1));
			    if (i + 2 < n) nxtm1 |= (1 << (i + 2));
			}
		    }
		    mat[mask][get_mask(nxtm1, nxtm2)] += 1;
		}
	    }
	}

	memset(res, 0, sizeof(res));
	for (int i = 0; i < (1 << (2*n)); i++)
	    res[i][i] = 1;

	// for (int r = 0; r < (1 << (2*n)); r++) {
	//     for (int c = 0; c < (1 << (2*n)); c++)
	// 	printf("%lld ", mat[r][c]);
	//     printf("\n");
	// }		

	while (m) {
	    if (m & 1) multiply(res, mat);
	    multiply(mat, mat);
	    m >>= 1;
	}

	// for (int r = 0; r < (1 << (2*n)); r++) {
	//     for (int c = 0; c < (1 << (2*n)); c++)
	// 	printf("%lld ", res[r][c]);
	//     printf("\n");
	// }		

	lint ans = 0;
	for (int i = 0; i < (1 << (2*n)); i++)
	    ans += res[0][i];
	
	cout << ans % MOD << endl;
    }
    return 0;
}
   
