#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int memo[2][MAXN][MAXN];
int get(int r, int c) { return r*8 + c; }
pii unget(int x) { return pii(x / 8, x % 8); }

int dr[] = {-1, 1, 2, 2, 1, -1, -2, -2};
int dc[] = {-2, -2, -1, 1, 2, 2, 1, -1};

int go(int k, int pk, int pc) {
    if (memo[k][pk][pc] != -1) return memo[k][pk][pc];
    int rk, ck, rc, cc;
    tie(rk, ck) = unget(pk);
    tie(rc, cc) = unget(pc);
    if (k == 0) {
        int iswin = 0;
        for (int i = 0; i < 8; i++) {
            int nr = rk + dr[i], nc = ck + dc[i];
            if (nr < 0 || nc < 0 || nr >= 8 || nc >= 8) continue;
            if (nr == rc && nc == cc) {
                iswin = 1;
                break;
            }
            if (go(1, get(nr, nc), pc) == 0) {
                iswin = 1;
                break;
            }
        }
        return memo[k][pk][pc] = iswin;
    }
    else {
        int iswin = 0;
        bool has = 0;
        for (int dc = -1; dc <= 1; dc += 2) {
            int nr = rc - 1, nc = cc + dc;
            if (nr < 0 || nc < 0 || nr >= 8 || nc >= 8) continue;
            if (nr == rk && nc == ck) {
                int nnr = nr - 1, nnc = nc + dc;
                if (nnr < 0 || nnc < 0 || nnr >= 8 || nnc >= 8) continue;
                iswin = 1;
                break;
            }
            if (nr == 0) {
                iswin = 1;
                break;
            }
            if (go(0, pk, get(nr, nc)) == 0) {
                iswin = 1;
                break;
            }
        }
        return memo[k][pk][pc] = iswin;
    }
}                

int main() {
    memset(memo, -1, sizeof(memo));
    string p, knight, checker;
    cin >> p >> knight >> checker;
    int pk = get(knight[1]-'1', knight[0]-'a');
    int pc = get(checker[1]-'1', checker[0]-'a');
    if (p == "black")
        printf("%s\n", go(1, pk, pc) ? "Black" : "White");
    else
        printf("%s\n", go(0, pk, pc) ? "White" : "Black");    
    return 0;
}
