#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Card {
    int color;
    int r, b;
    Card(int _c = 0, int _r = 0, int _b = 0) : color(_c), r(_r), b(_b) {}
};

Card card[18];

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        char c;
        int r, b;
        scanf(" %c%d%d", &c, &r, &b);
        card[i] = Card(c == 'R', r, b);
    }

    memset(dp, INF, sizeof(dp));
    dp[0][0][0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int nr = 0, nb = 0;
        int sr = 0, sb = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sr += card[i].r;
                sb += card[i].b;
                if (card[i].color == 0)
                    nb++;
                else
                    nr++;
            }
        }                
        for (int r = 0; r < 18; r++) {
            for (int b = 0; b < 18; b++) {
                if (dp[mask][r][b] == INF) continue;
                int n_taken = __builtin_popcount(mask);
                int disc = n_taken * (n_taken - 1) / 2;                
                int rt = dp[mask][r][b] - __builtin_popcount(mask) - sr + disc - r;
                int bt = dp[mask][r][b] - __builtin_popcount(mask) - sb + disc - b;
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) continue;
                    int disc_r = max(0, nr - card[j].r);
                    int disc_b = max(0, nb - card[j].b);
                    int add_t = max(max(0, card[j].r - nr - rt), max(0, card[j].b - nb - bt));
                    dp[mask | (1 << j)][r + disc_r][b + disc_b] = min(
                        dp[mask | (1 << j)][r + disc_r][b + disc_b],
                        dp[mask][r][b] + add_t + 1);
                }
            }
        }
    }
    int ans = INF;
    for (int r = 0; r < 18; r++)
        for (int c = 0; c < 18; c++)
            ans = min(ans, dp[(1 << n) - 1][r][c]);
    printf("%d\n", ans);        
    return 0;
}
