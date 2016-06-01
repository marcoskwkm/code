#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 310;
const int MAXP = MAXD*MAXD;

int tree[4][4*MAXD][4*MAXD];
//pii mudou[4][16*MAXD*MAXD];
vector<pii> mudou[4];
int len_mudou[4];
int n, m, p;

int query_col(int k, int ir, int i, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return INF;
    if (ql <= l && r <= qr) return tree[k][ir][i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return min(query_col(k, ir, L, l, mid, ql, qr),
               query_col(k, ir, R, mid + 1, r, ql, qr));
}

int query_row(int k, int i, int l, int r, int qrl, int qrr, int qcl, int qcr) {
    if (qrr < l || qrl > r) return INF;
    if (qrl <= l && r <= qrr) return query_col(k, i, 0, 0, m - 1, qcl, qcr);
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    return min(query_row(k, L, l, mid, qrl, qrr, qcl, qcr),
               query_row(k, R, mid + 1, r, qrl, qrr, qcl, qcr));
}

void update_col(int k, int ir, int i, int l, int r, int qc, int val) {
    if (qc < l || qc > r) return;
    // mudou[k][len_mudou[k]++] = pii(ir, i);
    mudou[k].push_back(pii(ir, i));
    if (l == r) {
        tree[k][ir][i] = val;
        return;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    update_col(k, ir, L, l, mid, qc, val);
    update_col(k, ir, R, mid + 1, r, qc, val);
    tree[k][ir][i] = min(tree[k][ir][L], tree[k][ir][R]);
}

int update_row(int k, int i, int l, int r, int qr, int qc, int val) {
    if (qr < l || qr > r) return query_col(k, i, 0, 0, m - 1, qc, qc);
    if (l == r) {
        update_col(k, i, 0, 0, m - 1, qc, val);
        return val;
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r)/2;
    int got = min(update_row(k, L, l, mid, qr, qc, val),
                  update_row(k, R, mid + 1, r, qr, qc, val));
    update_col(k, i, 0, 0, m - 1, qc, got);
    return got;
}

inline void update(int r, int c, int val) {
    update_row(0, 0, 0, n - 1, r, c, -r - c + val);
    update_row(1, 0, 0, n - 1, r, c, -r + c + val);
    update_row(2, 0, 0, n - 1, r, c, r - c + val);
    update_row(3, 0, 0, n - 1, r, c, r + c + val);
}    

vector<pii> pos[MAXP];
int bests[MAXD*MAXD];

int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int x;
            scanf("%d", &x);
            pos[x].push_back(pii(r, c));
        }
    }
    memset(tree, INF, sizeof(tree));
    int rp = pos[p][0].first, cp = pos[p][0].second;
    update(rp, cp, 0);
    for (int pp = p - 1; pp >= 1; pp--) {
        int cnt = 0;
        for (pii &chest: pos[pp]) {
            int r = chest.first, c = chest.second;
            int got = INF;
            got = min(got, query_row(0, 0, 0, n - 1, 0, r, 0, c) + r + c);
            got = min(got, query_row(1, 0, 0, n - 1, 0, r, c, m - 1) + r - c);
            got = min(got, query_row(2, 0, 0, n - 1, r, n - 1, 0, c) - r + c);
            got = min(got, query_row(3, 0, 0, n - 1, r, n - 1, c, m - 1) - r - c);
            bests[cnt++] = got;
        }
        for (int i = 0; i < 4; i++) {
            for (pii &mp: mudou[i])
                tree[i][mp.first][mp.second] = INF;
            mudou[i].clear();
            // for (int j = 0; j < len_mudou[i]; j++)
            //     tree[i][mudou[i][j].first][mudou[i][j].second] = INF;
            // len_mudou[i] = 0;
        }        
        for (int i = 0; i < (int)pos[pp].size(); i++) 
            update(pos[pp][i].first, pos[pp][i].second, bests[i]);
    }
    printf("%d\n", query_row(3, 0, 0, n - 1, 0, n - 1, 0, m - 1));
    return 0;
}
