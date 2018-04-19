#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 500;

bool m[3][MAXD];

bool go(int r, int c) {
    printf("%d %d\n", r + 200, c + 200);
    fflush(stdout);
    int x, y;
    scanf("%d%d", &x, &y);
    if (x < 0 || y < 0) exit(0);
    if (x == 0 && y == 0) return 1;
    m[x - 200][y - 200] = 1;
    return 0;
}    

int main() {
    int t;
    for (cin >> t; t--;) {
        memset(m, 0, sizeof(m));
        int n;
        scanf("%d", &n);
        bool done = 0;
        for (int c = 1; c < 66 && !done; c++)
            while (!done && !(m[0][c - 1] && m[1][c - 1] && m[2][c - 1]))
                if (go(1, c)) done = 1;
        while (!done)
            if (go(1, 65)) done = 1;
    }
    return 0;
}
