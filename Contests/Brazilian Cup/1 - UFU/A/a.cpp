#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010, MAXM = 110;

char str[MAXN][MAXM];
char sq[MAXM];
int ord[MAXM];

int main() {
    int n, m, q, k;
    scanf("%d%d%d%d", &n, &m, &q, &k);
    k = m - k;
    for (int i = 0; i < m; i++)
        ord[i] = i;
    
    for (int i = 0; i < n; i++)
        scanf("%s", str[i]);
    for (scanf("%d", &q); q--;) {
        scanf("%s", sq);
        random_shuffle(ord, ord + m);
        bool ok = 0;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                if (cnt + m - j < k) break;
                if (str[i][ord[j]] == sq[ord[j]])
                    cnt++;
                if (cnt == k) break;
            }
            if (cnt == k) {
                ok = 1;
                break;
            }
        }
        printf("%s\n", ok ? "S" : "N");
    }    
    return 0;
}
