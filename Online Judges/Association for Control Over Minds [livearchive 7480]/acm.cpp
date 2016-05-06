#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXI = (int)5e5 + 10, MAXN = (int)2e5 + 10;

bool foi[MAXI];
int cmp[MAXI];
vector<int> cmps[MAXI];
int recipe[MAXI];
int inrecipe[MAXI];

int main() {
    int n;
    while (scanf("%d", &n) > 0) {
        for (int i = 0; i < MAXI; i++) {
            cmp[i] = i;
            cmps[i] = {i};
        }
        memset(inrecipe, -1, sizeof(inrecipe));
        int ans = 0;
        while (n--) {
            int len;
            scanf("%d", &len);
            int maxsize = 0, maxid = -1;
            for (int i = 0; i < len; i++) {
                scanf("%d", &recipe[i]);
                inrecipe[recipe[i]] = n;
                foi[recipe[i]] = 0;
                if (cmps[cmp[recipe[i]]].size() > maxsize) {
                    maxsize = cmps[cmp[recipe[i]]].size();
                    maxid = cmp[recipe[i]];
                }
            }
            
            // check
            bool ok = 1;
            for (int i = 0; i < len && ok; i++) {
                if (foi[recipe[i]]) continue;
                for (int ing: cmps[cmp[recipe[i]]]) {
                    if (inrecipe[ing] != n) {
                        ok = 0;
                        break;
                    }
                    foi[ing] = 1;
                }
            }
            if (!ok) continue;

            ++ans;
            // merge
            for (int i = 0; i < len; i++) {
                int id = cmp[recipe[i]];
                if (id == maxid) continue;
                for (int ing: cmps[id]) {
                    cmps[maxid].push_back(ing);
                    cmp[ing] = maxid;
                }
                cmps[id].clear();
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
