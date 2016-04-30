#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXR = 100, MAXQ = (int)1e5 + 10;
const int MAXN = (int)1e5 + 10;

int freq_row[MAXR][MAXQ];
pii col[MAXN]; // <color, last appearance>
int freq_col[MAXR][MAXQ];
pii row[MAXN];
int n, q;

void bit_update(int *bit, int i, int val) {
    for (; i <= q; i += i & -i)
        bit[i] += val;
}

int bit_query(int *bit, int i) {
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret += bit[i];
    return ret;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int t = 1; t <= q; t++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int r, color;
            scanf("%d%d", &r, &color);
            if (row[r].second)
                bit_update(freq_col[row[r].first], row[r].second, -1);
            row[r] = pii(color, t);
            bit_update(freq_col[color], t, 1);
        }
        else if (op == 2) {
            int c, color;
            scanf("%d%d", &c, &color);
            if (col[c].second)
                bit_update(freq_row[col[c].first], col[c].second, -1);
            col[c] = pii(color, t);
            bit_update(freq_row[color], t, 1);
        }
        else if (op == 3) {
            int r;
            scanf("%d", &r);
            int q_last = n;
            int freq = 0, ans;
            for (int color = 0; color < MAXR; color++) {
                if (color == row[r].first) continue;
                int got = bit_query(freq_row[color], t) - bit_query(freq_row[color], row[r].second);
                q_last -= got;
                if (got >= freq) {
                    freq = got;
                    ans = color;
                }
            }
            if (q_last > freq) ans = row[r].first;
            else if (q_last == freq) ans = max(ans, row[r].first);
            printf("%d\n", ans);
        }
        else {
            int c;
            scanf("%d", &c);
            int q_last = n;
            int freq = 0, ans;
            for (int color = 0; color < MAXR; color++) {
                if (color == col[c].first) continue;
                int got = bit_query(freq_col[color], t) - bit_query(freq_col[color], col[c].second);
                q_last -= got;
                if (got >= freq) {
                    freq = got;
                    ans = color;
                }
            }
            if (q_last > freq) ans = col[c].first;
            else if (q_last == freq) ans = max(ans, col[c].first);
            printf("%d\n", ans);
        }
    }            
    return 0;
}
