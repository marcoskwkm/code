#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 10;

int n, m, t;
char grid[MAXD][MAXD];
int door_id[MAXD][MAXD];
int ndoors;

struct State {
    int r, c;
    int k[4];
    int md;
    int carrying;
    State() {}
    State(int rr, int cc, int kk[], int mdd) {
        r = rr; c = cc;
        carrying = 0;
        for (int i = 0; i < 4; i++) {
            k[i] = kk[i];
            if (k[i] == 1) carrying++;
        }
        md = mdd;
    }
    bool operator< (const State &that) const {
        tuple<int,int,int,int,int,int,int> t1(r, c, k[0], k[1], k[2], k[3], md);
        tuple<int,int,int,int,int,int,int> t2(that.r, that.c, that.k[0], that.k[1], that.k[2], that.k[3], that.md);
        return t1 < t2;
    }
};

char keys[] = "cdhs";
char doors[] = "CDHS";
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
    scanf("%d%d%d", &n, &m, &t);
    int sr, sc;
    int er, ec;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            scanf(" %c", &grid[r][c]);
            if (grid[r][c] == 'I') sr = r, sc = c;
            if (grid[r][c] == 'E') er = r, ec = c;
            if (grid[r][c] == 'C' || grid[r][c] == 'D' ||
                grid[r][c] == 'H' || grid[r][c] == 'S') {
                door_id[r][c] = ndoors++;
            }
        }
    }
    map<State, int> dist;
    int sk[] = {0, 0, 0, 0};
    State s(sr, sc, sk, 0);
    dist[s] = 0;
    deque<State> fila;
    fila.push_back(s);
    while (!fila.empty()) {
        State cur = fila.front();
        fila.pop_front();
        int d = dist[cur];
        // printf("(%d, %d) [%d, %d, %d, %d], %d: %d\n", cur.r, cur.c,
        //        cur.k[0], cur.k[1], cur.k[2], cur.k[3], cur.md, d);
        if (grid[cur.r][cur.c] == 'E') {
            printf("%d\n", d);
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            if (grid[cur.r][cur.c] == keys[i]) {
                if (cur.k[i] == 0 && cur.carrying < t) {
                    int nxtk[4];
                    for (int j = 0; j < 4; j++) nxtk[j] = cur.k[j];
                    nxtk[i] = 1;
                    State nxt(cur.r, cur.c, nxtk, cur.md);
                    if (dist.find(nxt) == dist.end()) {
                        dist[nxt] = d;
                        fila.push_front(nxt);
                    }
                }
            }
        }
        if (grid[cur.r][cur.c] == 'B') {
            for (int mask = 0; mask < (1 << 4); mask++) {
                bool ok = 1;
                for (int i = 0; i < 4; i++) {
                    if ((mask & (1 << i)) && cur.k[i] == 0) {
                        ok = 0;
                        break;
                    }
                }
                if (!ok) continue;
                int nxtk[4];
                for (int i = 0; i < 4; i++) {
                    if (cur.k[i]) {
                        if (mask & (1 << i)) nxtk[i] = 3 - cur.k[i];
                        else nxtk[i] = cur.k[i];
                    }
                    else nxtk[i] = 0;
                }
                State nxt(cur.r, cur.c, nxtk, cur.md);
                if (dist.find(nxt) == dist.end()) {
                    dist[nxt] = d;
                    fila.push_front(nxt);
                }
            }
        }
        for (int dir = 0; dir < 4; dir++) {
            int nr = cur.r + dx[dir], nc = cur.c + dy[dir];
            if (nr >= n || nc >= m || nr < 0 || nc < 0) continue;
            if (grid[nr][nc] == '#') continue;
            bool ok = 1;
            int nxtmd = cur.md;
            for (int i = 0; i < 4; i++) {
                if (grid[nr][nc] == doors[i]) {
                    if (!(nxtmd & (1 << door_id[nr][nc])) && cur.k[i] != 1) {
                        ok = 0;
                        break;
                    }
                    else nxtmd |= (1 << door_id[nr][nc]);
                }
            }
            if (!ok) continue;
            State nxt(nr, nc, cur.k, nxtmd);
            if (dist.find(nxt) == dist.end()) {
                dist[nxt] = d + 1;
                fila.push_back(nxt);
            }
        }
    }
    printf("-1\n");    
    return 0;
}
