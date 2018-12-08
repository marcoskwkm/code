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
    for (cin >> t; t--;) {
        int n;
        string s;
        cin >> n >> s;
        bool ok = 1;
        lint ans = 0;
        int cur = -INF;
        int cnt = 0;
        bool flag = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '.') {
                flag = 1;
                continue;
            }
            if (flag) {
                cur = max(i, cur + 2);
                if (cur + 1 >= (int)s.size()) ok = 0;
                ans += abs(cur - i) + cur - cnt;
            }
            cnt++;
        }
        printf("%lld\n", ok ? ans : -1);
    }        
    return 0;
}
