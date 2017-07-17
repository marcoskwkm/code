#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef unsigned long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

int dig[MAXN];
int len;

lint dp[MAXN][10][2][2];
bool done[MAXN][10][2][2];

lint go(int i, int last, int dir, int free) {
    if (i == len) return 1;
    lint &ret = dp[i][last][dir][free];
    if (done[i][last][dir][free]) return ret;
    ret = 0;
    for (int d = 0; d <= 9; d++) {
        // for (int k = 0; k < i; k++) printf(" ");
        if (d > dig[i] && !free) break;
        // printf("%d\n", d);
        if (d < last) ret += go(i + 1, d, 0, free || (d < dig[i]));
        else if (d == last) ret += go(i + 1, d, dir, free || (d < dig[i]));
        else if (dir == 1) ret += go(i + 1, d, 1, free || (d < dig[i]));
    }
    done[i][last][dir][free] = 1;
    return ret;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        string s;
        cin >> s;
        len = 0;
        int up = 1;
        char last = '0';
        bool ok = 1;
        for (char c: s) {
            dig[len++] = c - '0';
            if (c > last && !up) ok = 0;
            if (c < last) up = 0;
            last = c;
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }
        memset(done, 0, sizeof(done));
        cout << go(0, 0, 1, 0) - 1 << endl;
    }        
    return 0;
}
