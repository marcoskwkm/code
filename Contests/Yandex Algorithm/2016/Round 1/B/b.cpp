#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int m[4][4];
int cur[4][4];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool go(int r, int c, int d) {
    if (r < 0 || c < 0 || r > 2 || c > 2) return 0;
    if (m[r][c] != -1 && m[r][c] != d) return 0;
    if (cur[r][c] != 0) return 0;
    cur[r][c] = d;
    if (d == 9) return 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (go(nr, nc, d + 1)) return 1;
    }
    cur[r][c] = 0;
    return 0;
}    

int main() {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            char d;
            scanf(" %c", &d);
            if (isdigit(d)) m[r][c] = d - '0';
            else m[r][c] = -1;
        }
    }
    assert(go(1, 1, 1));
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++)
            printf("%d", cur[r][c]);
        printf("\n");
    }
    return 0;
}
