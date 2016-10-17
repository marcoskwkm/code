#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int ansa[MAXN], ansb[MAXN];

int main() {
    set< tiii, greater<tiii> > cj;
    int n, m;
    scanf("%d%d", &n, &m);
    map<int, vector<int>> rem;
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        rem[p].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int s;
        scanf("%d", &s);
        cj.insert(tiii(s, 0, i));
    }

    int ansc = 0, ansu = 0;
    while (!cj.empty()) {
        int p, na, id;
        tie(p, na, id) = *cj.begin();
        cj.erase(cj.begin());
        if (rem.find(p) != rem.end()) {
            vector<int> &v = rem[p];
            if (v.size() > 0) {
                int i = v.back();
                v.pop_back();
                ansb[i] = id + 1;
                ansa[id] = -na;
                ansc++;
                ansu -= na;
                continue;
            }
        }
        if (p == 1) continue;
        p = (p + 1) / 2;
        na--;
        cj.insert(tiii(p, na, id));
    }
    printf("%d %d\n", ansc, ansu);
    for (int i = 0; i < m; i++)
        printf("%d%c", ansa[i], i + 1 == m ? '\n' : ' ');
    for (int i = 0; i < n; i++)
        printf("%d%c", ansb[i], i + 1 == n ? '\n' : ' ');    
    return 0;
}
