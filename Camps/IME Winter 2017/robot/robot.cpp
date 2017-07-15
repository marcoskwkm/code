#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 1010;

char grid[MAXD][MAXD];
int n, m, k;
char seq[2 * MAXD];
int len;
string ans;
int best;

void go(int r, int c) {
    if (r == n || c == m) {
        for (int sub = 1; sub <= len && sub <= k; sub++) {
            bool ok = 1;
            for (int j = sub; j < len && ok; j += sub) {
                for (int i = 0; i < sub && i + j < len; i++) {
                    if (seq[j + i] != seq[i]) {
                        ok = 0;
                        break;
                    }
                }
            }
            if (ok) {
                char prev = seq[sub];
                seq[sub] = 0;
                string got(seq);
                if (sub < best) {
                    best = sub;
                    ans = got;
                }
                else if (sub == best)
                    ans = min(ans, got);
                seq[sub] = prev;
                break;
            }
        }
        return;
    }
    if (c + 1 == m || grid[r][c + 1] == '.') {
        seq[len++] = '0';
        go(r, c + 1);
        len--;
    }
    if (r + 1 == n || grid[r + 1][c] == '.') {
        seq[len++] = '1';
        go(r + 1, c);
        len--;
    }
}

int main() {
    cin >> n >> k;
    m = n;
    int sr, sc;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            scanf(" %c", &grid[r][c]);
            if (grid[r][c] == 'R')
                sr = r, sc = c;
        }
    }
    len = 0;
    ans = "2";
    best = 1327490813;
    go(sr, sc);
    printf("%s\n", ans.c_str());    
    return 0;
}
