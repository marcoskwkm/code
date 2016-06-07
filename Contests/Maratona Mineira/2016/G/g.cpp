#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    for (int d = 1; d <= n; d++) {
        if (n % d) continue;
        int l = 0, r = n - 1;
        bool ok = 1;
        while (l < r) {
            if (s.substr(l, d) != s.substr(r - d + 1, d)) {
                ok = 0;
                break;
            }
            l += d, r -= d;
        }
        if (ok) {
            printf("%d\n", n / d);
            return 0;
        }
    }                
    return 0;
}
