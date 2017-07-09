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
        string s;
        cin >> s;
        int n = s.size();
        if (n & (n - 1)) printf("NO\n");
        else if (n ==1 ) printf("YES\n");
        else {
            bool ok = 1;
            for (size_t i = 0; i < s.size(); i += 2) {
                if (s[i] == 'A' && s[i + 1] == 'A') {
                    ok = 0;
                    break;
                }
            }
            printf("%s\n", ok ? "YES" : "NO");
        }
    }        
    return 0;
}
