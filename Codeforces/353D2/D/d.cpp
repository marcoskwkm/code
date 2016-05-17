#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    scanf("%d", &n);
    int a1;
    scanf("%d", &a1);
    set< pii, greater<pii> > cj;
    cj.insert(pii(1, a1));
    for (int i = 2; i <= n; i++) {
        int ai;
        scanf("%d", &ai);
        pii np(ai, INF);
        pii parent = *cj.lower_bound(np);
        printf("%d", parent.second);
        cj.erase(parent);
        np.second = ai;
        if (ai < parent.second) {
            np.first = parent.first;
            parent.first = parent.second;
            auto it = cj.lower_bound(pii(parent.second + 1, INF));
            if (it == cj.end() || it->first != parent.second + 1) {
                cj.insert(parent);
            }
        }
        else {
            np.first = parent.second + 1;
            if (parent.first < parent.second) {
                cj.insert(parent);
            }
        }
        cj.insert(np);
        printf("%c", i == n ? '\n' : ' ');
    }    
    return 0;
}
