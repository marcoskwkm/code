const int MAXN = 110;

int MOD;
int inv[MAXN];

int mat[MAXN][MAXN];
int idx[MAXN];   // row index
int pivot[MAXN]; // pivot of row i

// Solves Ax = B, where A is a neq x nvar matrix and B is mat[*][nvar].
// Returns a vector of free variables
// (empty if system is defined, {-1} if no solution exists).
// Reduces matrix to reduced echelon form.
vector<int> solve(int nvar, int neq) {
    for (int i = 0; i < neq; i++) idx[i] = i;
    int currow = 0;
    vector<int> freeVars;
    for (int col = 0; col < nvar; col++) {
        int pivotrow = -1;
        for (int row = currow; row < neq; row++) {
            if (mat[idx[row]][col] != 0) {
                pivotrow = row;
                break;
            }
        }
        if (pivotrow == -1) { freeVars.push_back(col); continue; }
        swap(idx[currow], idx[pivotrow]);
        pivot[currow] = col;
        for (int c = 0; c <= nvar; c++) {
            if (c == col) continue;
            mat[idx[currow]][c] =
                (mat[idx[currow]][c] * inv[mat[idx[currow]][col]]) % MOD;
        }
        mat[idx[currow]][col] = 1;
        for (int row = 0; row < neq; row++) {
            if (row == currow) continue;
            int k = (mat[idx[row]][col] * inv[mat[idx[currow]][col]]) % MOD;
            for (int c = 0; c <= nvar; c++)
                mat[idx[row]][c] =
                    ((mat[idx[row]][c] - k * mat[idx[currow]][c]) % MOD + MOD) % MOD;
        }
        currow++;
    }
    for (int row = currow; row < neq; row++)
        if (mat[idx[row]][nvar] != 0) return vector<int>(1, -1);
    return freeVars;
}
