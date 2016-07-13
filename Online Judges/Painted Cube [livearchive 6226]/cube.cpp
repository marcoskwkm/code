#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 22;

// URLD
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, 1, -1, 0};
const vector<int> dir[] = {
    {1, 5, 2, 3, 0, 4},
    {3, 1, 0, 5, 4, 2},
    {2, 1, 5, 0, 4, 3},
    {4, 0, 2, 3, 5, 1}
};

int rotate(int cube, vector<int> aux) {
    int ret = 0;
    for (int i = 0; i < 6; i++)
        ret |= (!!(cube & (1 << aux[i])) << i);
    return ret;
}
        
int ri[MAXN], ci[MAXN];
int idx[MAXN][MAXN];

int main() {
    vector<string> grid;
    string line;
    bool cont = 1;
    while (cont) {
        grid.clear();
        while (1) {
            if (!getline(cin, line)) {
                cont = 0;
                break;
            }
            if (line == "") break;
            grid.push_back(line);
        }
        int n = grid.size();
        int m = grid[0].size();
        int cnt = 0;
        int sr, sc, gr, gc;
        int mask = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == 'C') {
                    sr = r, sc = c;
                    grid[r][c] = '.';
                }
                if (grid[r][c] == 'G') {
                    gr = r, gc = c;
                    grid[r][c] = '.';
                }
                if (grid[r][c] == 'P') {
                    grid[r][c] = '.';
                    mask |= (1 << cnt);
                }
                if (grid[r][c] == '.') {
                    ri[cnt] = r, ci[cnt] = c;
                    idx[r][c] = cnt++;
                }
            }
        }
        queue< tuple<int, int, int, int> > q;
        map< tuple<int, int, int, int>, int > dist;
        auto init_state = make_tuple(0, sr, sc, mask);
        dist[init_state] = 0;
        q.push(init_state);
        bool found = 0;
        while (!q.empty()) {
            int r, c, cube;
            auto state = q.front();
            tie(cube, r, c, mask) = state;
            q.pop();
            int d = dist[state];
            // printf("Position: %d, %d (d = %d)\n", r, c, d);
            // printf("Cube:");
            // for (int i = 0; i < 6; i++) printf(" %d", cube.sides[i]);
            // printf("\n");

            // check if reached final state
            if (mask == (1 << idx[gr][gc]) && r == gr && c == gc && (cube & 1) == 0) {
                printf("%d\n", d);
                found = 1;
                break;
            }

            // color transition
            if (!!(mask & (1 << idx[r][c])) ^ (cube & 1)) {
                mask ^= (1 << idx[r][c]);
                cube ^= 1;
            }
            
            // move cube
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if (grid[nr][nc] == '#') continue;
                int newcube = rotate(cube, dir[i]);
                auto newstate = make_tuple(newcube, nr, nc, mask);
                if (dist.find(newstate) == dist.end()) {
                    dist[newstate] = d + 1;
                    q.push(newstate);
                }
            }
        }
        if (!found) printf("-1\n");
    }        
    return 0;
}
