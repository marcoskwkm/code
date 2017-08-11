#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 110;

char grid[MAXD][MAXD];

int main() {
    int n, m;
    cin >> n >> m;
    set<char> cj;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            scanf(" %c", &grid[r][c]);
            cj.insert(grid[r][c]);
        }
    }
    if (cj.size() != 3) {
        printf("NO\n");
        return 0;
    }
       
    bool ans = 0;
    for (int s = 0; s < 2; s++) {
        if (n % 3 == 0) {
            int k = n / 3;
            bool ok = 1;
            for (int i = 0; i < 3; i++)
                for (int r = 0; r < k; r++)
                    for (int c = 0; c < m; c++)
                        if (grid[i * k + r][c] != grid[i * k][0])
                            ok = 0;
            if (ok) ans = 1;
        }
        for (int r = 0; r < max(n, m); r++)
            for (int c = r; c < max(n, m); c++)
                swap(grid[r][c], grid[c][r]);
        swap(n, m);
        // printf("---\n");
        // for (int r = 0; r < n; r++) {
        //     for (int c = 0; c < m; c++)
        //         printf("%c", grid[r][c]);
        //     printf("\n");
        // }
    }
    printf("%s\n", ans ? "YES" : "NO");    
    return 0;
}
