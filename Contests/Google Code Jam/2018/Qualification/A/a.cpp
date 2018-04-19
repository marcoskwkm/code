#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);
        int d;
        string s;
        cin >> d >> s;
        multiset<int, greater<int>> ms;
        lint cur = 1;
        lint damage = 0;
        for (char c: s) {
            if (c == 'S') {
                ms.insert(cur);
                damage += cur;
            }
            else cur *= 2;
        }
        int ans = 0;
        while (damage > d && !ms.empty() && *ms.begin() > 1) {
            lint dmg = *ms.begin();
            ms.erase(ms.begin());
            ms.insert(dmg / 2);
            damage -= dmg / 2;
            ans++;
        }
        if (damage > d) printf("IMPOSSIBLE\n");
        else printf("%d\n", ans);
    }
    return 0;
}
