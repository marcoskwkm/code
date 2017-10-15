#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int grid[4][4];
vector<pii> sol;
vector<pii> order;
vector<pii> best;

bool check(int r, int c) {
    for (int i = 1; i <= 3; i++) {
        if (grid[i][1] == grid[i][2] && grid[i][1] == grid[i][3] && grid[i][1] != 0)
            return 1;
        if (grid[1][i] == grid[2][i] && grid[1][i] == grid[3][i] && grid[1][i] != 0)
            return 1;
    }
    if (grid[1][1] == grid[2][2] && grid[1][1] == grid[3][3] && grid[1][1] != 0)
        return 1;
    if (grid[1][3] == grid[2][2] && grid[1][3] == grid[3][1] && grid[1][3] != 0)
        return 1;    
    return 0;
}

void go() {
    pii bob(-1, -1);
    for (pii p: order) {
        if (grid[p.first][p.second] == 0) {
            bob = p;
            break;
        }
    }
    if (bob.first == -1) return;
    grid[bob.first][bob.second] = 1;
    if (check(bob.first, bob.second)) {
        if (best.empty() || sol.size() < best.size())
            best = sol;
    }
    else {
        for (int r = 1; r <= 3; r++) {
            for (int c = 1; c <= 3; c++) {
                if (grid[r][c] == 0) {
                    grid[r][c] = 2;
                    sol.push_back(pii(r, c));
                    if (!check(r, c)) go();
                    sol.pop_back();
                    grid[r][c] = 0;
                }
            }
        }                    
    }
    grid[bob.first][bob.second] = 0;
}


int main() {
    for (int i = 0; i < 9; i++) {
        int r, c;
        scanf("%d%d", &r, &c);
        order.push_back(pii(r, c));
    }
    go();
    for (pii p: best)
        printf("%d %d\n", p.first, p.second);    
    return 0;
}
