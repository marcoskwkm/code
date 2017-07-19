#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> tiiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 52;

int active[MAXN][MAXN][MAXN];
int acc[MAXN][MAXN][MAXN];

void recalc(int n) {
    for (int x = 2; x < n + 2; x++)
        for (int y = 2; y < n + 2; y++)
            for (int z = 2; z < n + 2; z++)
                acc[x][y][z] = active[x][y][z] + acc[x - 1][y][z]
                    + acc[x][y - 1][z] + acc[x][y][z - 1]
                    - acc[x - 1][y - 1][z] - acc[x - 1][y][z - 1]
                    - acc[x][y - 1][z - 1] + acc[x - 1][y - 1][z - 1];
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        scanf("%d", &n);
        vector<tiiii> v;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                for (int z = 0; z < n; z++) {
                    int f;
                    scanf("%d", &f);
                    v.push_back(tiiii(f, x, y, z));
                }
            }
        }
        memset(acc, 0, sizeof(acc));
        memset(active, 0, sizeof(active));
        int at = 0;
        sort(v.begin(), v.end());
        for (int nn = 1; nn <= n; nn++) {
            int before = 0;
            for (int x = nn + 1; x < n + 2; x++) {
                for (int y = nn + 1; y < n + 2; y++) {
                    for (int z = nn + 1; z < n + 2; z++) {
                        int q = acc[x][y][z] - acc[x - nn][y][z]
                            - acc[x][y - nn][z] - acc[x][y][z - nn]
                            + acc[x - nn][y - nn][z] + acc[x - nn][y][z - nn]
                            + acc[x][y - nn][z - nn]
                            - acc[x - nn][y - nn][z - nn];
                        if (q == nn * nn * nn) before++;
                    }
                }
            }
            while (at < (int)v.size() && get<0>(v[at]) <= nn) {
                int f, x, y, z;
                tie(f, x, y, z) = v[at++];
                active[x + 2][y + 2][z + 2] = 1;
            }
            recalc(n);
            int ans = 0;
            for (int x = nn + 1; x < n + 2; x++) {
                for (int y = nn + 1; y < n + 2; y++) {
                    for (int z = nn + 1; z < n + 2; z++) {
                        int q = acc[x][y][z] - acc[x - nn][y][z]
                            - acc[x][y - nn][z] - acc[x][y][z - nn]
                            + acc[x - nn][y - nn][z] + acc[x - nn][y][z - nn]
                            + acc[x][y - nn][z - nn]
                            - acc[x - nn][y - nn][z - nn];
                        if (q == nn * nn * nn) ans++;
                    }
                }
            }
            printf("%d ", ans - before);
        }
        printf("\n");
    }
    return 0;
}
