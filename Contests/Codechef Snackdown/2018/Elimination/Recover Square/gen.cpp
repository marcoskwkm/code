#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr, x)

typedef pair<int, int> pii;

const int MAXN = 210;

int mat[MAXN][MAXN];

int main(int argc, char* argv[]) {
    int n;
    sscanf(argv[1], "%d", &n);

    srand(time(0));
    int sum = 0;
    vector<int> v;
    for (int i = 1; i <= n * n; i++)
        v.push_back(i);
    random_shuffle(v.begin(), v.end());

    int cnt = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            mat[r][c] = v[cnt++];

    vector<pii> edges;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            for (int dr = -2; dr <= 2; dr++) {
                for (int dc = -2; dc <= 2; dc++) {
                    int dist = abs(dr) + abs(dc);
                    if (dist == 0 || dist > 2) continue;
                    int rr = r + dr, cc = c + dc;
                    if (rr < 0 || cc < 0 || rr >= n || cc >= n) continue;
                    if (mat[r][c] > mat[rr][cc]) continue;
                    edges.push_back(pii(mat[r][c], mat[rr][cc]));
                }
            }
        }
    }

    printf("1\n%d %d\n", n, (int)edges.size());
    for (pii p: edges)
        printf("%d %d\n", p.first, p.second);

    // debug("Solution:\n");
    // for (int r = 0; r < n; r++) {
    //     for (int c = 0; c < n; c++)
    //         debug("%d ", mat[r][c]);
    //     debug("\n");
    // }

    return 0;
}
