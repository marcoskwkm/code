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
    int t;
    for (scanf("%d", &t); t--;) {
        int n, k;
        scanf("%d%d", &n, &k);
        string s;
        cin >> s;
        int ans = 0;
        bool possible = 0;
        for (size_t i = 0; i < s.size();) {
            size_t j = i;
            while (j + 1 < s.size() && s[j + 1] == s[i]) j++;
            int len = j - i + 1;
            if (len >= k) possible = 1;
            ans += (len + k - 1) / k;
            i = j + 1;
        }
        if (!possible) printf("-1\n");
        else printf("%d\n", ans);
    }        
    return 0;
}
