#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55;

lint availR[MAXN], availC[MAXN];
lint optR[MAXN][MAXN], optC[MAXN][MAXN];
lint occR[MAXN], occC[MAXN];
int mat[MAXN][MAXN];
pii marked[MAXN * MAXN][MAXN * MAXN];
int n, k;

void mark(int r, int c, int val) {
    mat[r][c] = val;
    availR[r] ^= (1LL << val);
    availC[c] ^= (1LL << val);
    optR[r][val] ^= (1LL << c);
    optC[c][val] ^= (1LL << r);
}

void unmark(int r, int c) {
    availR[r] ^= (1LL << mat[r][c]);
    availC[c] ^= (1LL << mat[r][c]);
    optR[r][mat[r][c]] ^= (1LL << c);
    optC[c][mat[r][c]] ^= (1LL << r);
    mat[r][c] = -1;
}

bool solveRem(int q) {
    if (q == n * n) return 1;

    int nr = -1, nc = -1, best = INF;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (mat[r][c] != -1) continue;
            int avail = __builtin_popcountll(availR[r] & availC[c]);
            if (avail < best) {
                best = avail;
                nr = r, nc = c;
            }
        }
    }

    for (lint availMask = availR[nr] & availC[nc]; availMask > 0; availMask -= availMask & -availMask) {
        int val = __builtin_ctzll(availMask);
        mark(nr, nc, val);

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int nxt = 1; nxt <= n; nxt++) {
                int maskR = occR[i] & optR[i][nxt], maskC = occC[i] & optC[i][nxt];
                if ((maskR & -maskR) == 0) {
                    int idx = __builtin_ctzll(maskR);
                    mark(i, idx, nxt);
                    marked[q][cnt++] = pii(i, idx);
                }
                else if ((maskC & -maskC) == 0) {
                    int idx = __builtin_ctzll(maskC);
                    mark(idx, i, nxt);
                    marked[q][cnt++] = pii(idx, i);
                }
            }
        }

        if (solveRem(q + 1)) return 1;
        unmark(nr, nc);

        for (int i = 0; i < cnt; i++) {
            unmark(marked[q][i].first, marked[q][i].second);
        }
    }

    return 0;
}

bool solve(int i, int last = 1, int left = k) {
    for (int j = 0; j < n - 2; j++) {
        mark(j, j, 1);
    }
    mark(n - 2, n - 2, 2);
    mark(n - 1, n - 1, 2);
    mark(n - 2, n - 1, 1);
    return solveRem(n + 1);
    // mark(0, 0, 1);
    // mark(0, 1, 2);
    // mark(1, 0, 2);
    // mark(1, 1, 1);
    // return solveRem(4);

    // if (i == n) {
    //     if (left != 0) return 0;
    //     bool almostAllEqual = 1;
    //     for (int j = 1; j < n - 1; j++) {
    //         if (mat[j][j] != mat[0][0]) {
    //             almostAllEqual = 0;
    //         }
    //     }
    //     if (almostAllEqual) return false;

    //     mark(n - 2, n - 1, 1);
    //     mark(n - 1, n - 2, 1);

    //     return solveRem(0, 1);
    // }
    // if ((left > (n - i) * n) || (left < (n - i) * last)) return 0;

    // for (int val = last; val <= min(left, n); val++) {
    //     mark(i, i, val);
    //     if (solve(i + 1, val, left - val)) return 1;
    //     unmark(i, i);
    // }

    return 0;
}

void calcAll() {
    for (n = 3; n <= 50; n += 2) {
        memset(mat, -1, sizeof(mat));
//        for (k = n + 2; 2 * k <= n * n + n; k++) {
        k = n + 2;
            printf("n = %d, k = %d: ", n, k);
            for (int i = 0; i < n; i++) {
                availR[i] = availC[i] = 0;
                occR[i] = occC[i] = (1LL << n) - 1;
                for (int val = 1; val <= n; val++) {
                    availR[i] ^= (1LL << val);
                    availC[i] ^= (1LL << val);
                    optR[i][val] = optC[i][val] = (1LL << n) - 1;
                }
            }

            int a = ((n - k) % n + n) % n;
            int last = (k + a - n) / n;
            if (last > 1 && (a == 1 || a == n - 1)) {
                last--;
            }

            if (k == n + 1 || !solve(0, last)) {
                printf("IMPOSSIBLE\n");
            } else {
                printf("POSSIBLE (last = %d)\n", last);
                for (int r = 0; r < n; r++) {
                    for (int c = 0; c < n; c++) {
                        printf("%2d ", mat[r][c]);
                    }
                    printf("\n");
                }
            }
//        }
    }
}

int main() {
    calcAll();
    return 0;
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            availR[i] = availC[i] = 0;
            for (int val = 1; val <= n; val++) {
                availR[i] ^= (1LL << val);
                availC[i] ^= (1LL << val);
            }
        }

        printf("Case #%d: ", t);

        if (k == n + 1 || !solve(0)) {
            printf("IMPOSSIBLE\n");
        } else {
            printf("POSSIBLE\n");
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    printf("%2d ", mat[r][c]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}
