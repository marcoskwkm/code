#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

char sol[MAXN];

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<tiii> v;
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            v.push_back(tiii(l, r, i));
        }
        sort(v.begin(), v.end(), [](tiii a, tiii b) { return get<0>(a) < get<0>(b); });

        int lastC = -1, lastJ = -1;
        bool flag = 0;
        for (tiii task: v) {
            int l, r, i;
            tie(l, r, i) = task;
            if (lastC <= l) {
                sol[i] = 'C';
                lastC = r;
            } else if (lastJ <= l) {
                sol[i] = 'J';
                lastJ = r;
            } else {
                flag = 1;
                break;
            }
        }
        printf("Case #%d: ", t);
        if (flag) {
            printf("IMPOSSIBLE\n");
        } else {
            sol[n] = 0;
            printf("%s\n", sol);
        }
    }
    return 0;
}
