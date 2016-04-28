#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef pair<pii, int> ppi;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;

pii in[MAXN];
map< pii, vector<int> > mp;
int ans[MAXN];
int group[MAXN];
vector<int> groups[MAXN];
int paired[MAXN];
int tem[MAXN];
bool foi[MAXN];
int n;

bool check_valid() {
    vector<pii> p1, p2;
    for (int i = 0; i < n; i++) {
        if (ans[i]) p2.push_back(in[i]);
        else p1.push_back(in[i]);
    }
    sort(p1.begin(), p1.end());
    sort(p2.begin(), p2.end());
    int i = 0, j = 0;
    int s1 = p1.size(), s2 = p2.size();
    while (i < s1 || j < s2) {
        if (i < s1 && p1[i] == pii(i, s2 - j)) {
            i++;
            continue;
        }
        if (j < s2 && p2[j] == pii(j, s1 - i)) {
            j++;
            continue;
        }
        return 0;
    }
    return 1;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        mp.clear();
        scanf("%d", &n);
        int s1 = 0, s2 = 0;
        int q = 2;
        for (int i = 0; i < n; i++) {
            paired[i] = -1;
            tem[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            in[i] = pii(a, b);
            if (tem[a] != -1) s2 = max(s2, a + 1);
            else s1 = max(s1, a + 1);
            tem[a] = i;
            if (mp.find(pii(a, b)) != mp.end()) {
                int prv = mp[pii(a, b)].back();
                paired[prv] = i;
                paired[i] = prv;
                // printf("pair %d - %d\n", i, prv);
                q = (q << 1) % MOD;
            }
            mp[pii(a, b)].push_back(i);
            groups[i].clear();
        }
        int i1 = 0, i2 = 0;
        int cur_group = 0;
        while (i1 < s1 || i2 < s2) {
            int ii = -1, ij = -1;
            vector<int> &vi = mp[pii(i1, s2 - i2)];
            vector<int> &vj = mp[pii(i2, s1 - i1)];
            if (i1 < s1 && !vi.empty()) ii = vi.back();
            if (i2 < s2 && !vj.empty()) ij = vj.back();
            assert(ii != -1 || ij != -1);
            if (ii != -1 && ij != -1) {
                if (s1 == s2) cur_group++;
                ans[ij] = 1;
                group[ij] = cur_group;
                groups[cur_group].push_back(ij);
                vj.pop_back();
                i2++;
            }
            else if (ii != -1) {
                ans[ii] = 0;
                group[ii] = cur_group;
                groups[cur_group].push_back(ii);
                vi.pop_back();
                i1++;
            }
            else {
                ans[ij] = 1;
                group[ij] = cur_group;
                groups[cur_group].push_back(ij);
                vj.pop_back();
                i2++;
            }
        }
        for (int i = 1; i < cur_group; i++)
            q = (q << 1) % MOD;
        printf("%d\n", q);

        // printf("before: ");
        // for (int i = 0; i < n; i++) printf("%d", ans[i]);
        // printf("\n");

        for (int i = 0; i <= cur_group; i++) {
            foi[i] = 0;
            sort(groups[i].begin(), groups[i].end());
        }
        for (int i = 0; i < n; i++) {
            if (foi[group[i]]) continue;
            foi[group[i]] = 1;
            int first = -1;
            for (int j: groups[group[i]]) {
                if (paired[j] != -1) {
                    if (paired[j] < j) continue;
                    ans[j] = 0;
                    ans[paired[j]] = 1;
                }
                else {
                    if (first == -1) first = ans[j];
                    ans[j] ^= first;
                }
            }
        }

        // printf("after: ");
        for (int i = 0; i < n; i++)
            printf("%d", ans[i]);
        printf("\n");

        assert(check_valid());
    }        
    return 0;
}
