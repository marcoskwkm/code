#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2050;

char grid[MAXN][MAXN];
vector<int> loses_to[MAXN];

int main() {
    int n;
    while (scanf("%d", &n) > 0 && n) {
        for (int r = 0; r < n; r++) {
            loses_to[r].clear();
            for (int c = 0; c < n; c++) 
                scanf(" %c", &grid[r][c]);
        }
        
        vector<int> wins;
        for (int i = 1; i < n; i++) {
            if (grid[0][i] == '1')
                wins.push_back(i);
            else {
                for (int j = 1; j < n; j++) {
                    if (i == j || grid[0][j] == '0') continue;
                    if (grid[j][i] == '1') {
                        loses_to[j].push_back(i);
                        break;
                    }
                }
            }
        }
        
        sort(wins.begin(), wins.end(), [](int a, int b) {
            return loses_to[a].size() > loses_to[b].size();
        });

        vector<int> ans;
        for (int i = 0; i < (int)wins.size(); i++) {
            int x = wins[i];
            int size = loses_to[x].size() + 1;
            vector<int> take;
            while (size != (size & -size)) {
                take.push_back(wins.back());
                wins.pop_back();
                size++;
            }
            ans.push_back(x + 1);
            for (int y: loses_to[x]) ans.push_back(y + 1);
            for (int y: take) ans.push_back(y + 1);
        }

        ans.push_back(1);
        while (ans.size() > 1) {
            vector<int> nxt;
            for (int i = 0; i < (int)ans.size(); i += 2) {
                int u = ans[i], v = ans[i + 1];
                printf("%d %d\n", u, v);
                if (grid[u - 1][v - 1] == '1') nxt.push_back(u);
                else nxt.push_back(v);
            }
            ans.clear();
            for (int x: nxt) ans.push_back(x);
        }
    }        
    return 0;
}
