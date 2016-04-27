#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;

vector<pii> v[MAXN];
vector<pii> same;
int sol[MAXN];
int sol2[MAXN];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        int hi = 0;
        scanf("%d", &n);
        int ans = 2;
        same.clear();
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (!v[a].empty() && v[a].back().first == b) {
                ans = (ans << 1) % MOD;
                same.push_back(pii(v[a].back().second, i));
            }
            v[a].push_back(pii(b, i));
            hi = max(hi, a);
        }
        printf("%d\n", ans);
        int s1 = hi + 1;
        int s2 = n - s1;
        int i = 0, j = 0;
        while (i < s1 || j < s2) {
            bool found = 0;
            if (i < s1) {
                for (pii &p: v[i]) {
                    if (p.first == s2 - j) {
                        printf("take (%d, %d) to 0\n", i, p.first);
                        sol[p.second] = 0;
                        swap(p, v[i].back());
                        v[i].pop_back();
                        found = 1;
                        i++;
                        break;
                    }
                }
            }
            if (!found && j < s2) {
                for (pii &p: v[j]) {
                    if (p.first == s1 - i) {
                        printf("take (%d, %d) to 1\n", j, p.first);
                        sol[p.second] = 1;
                        swap(p, v[j].back());
                        v[j].pop_back();
                        found = 1;
                        j++;
                        break;
                    }
                }
            }
            assert(found);
        }
        for (int i = 0; i < n; i++)
            sol2[i] = sol[i] ^ 1;
        for (pii p: same) {
            if (sol[p.first])
                swap(sol[p.first], sol[p.second]);
            else
                swap(sol2[p.first], sol2[p.second]);
        }

        bool take_first = 1;

        for (int i = 0; i < n; i++) {
            if (sol2[i] < sol[i]) {
                take_first = 0;
                break;
            }
            if (sol[i] < sol2[i]) break;
        }
        
        for (int i = 0; i < n; i++) printf("%d", sol[i]);
        printf("\n");        
        
        for (int i = 0; i <= hi; i++) v[i].clear();
    }        
    return 0;
}
