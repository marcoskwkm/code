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
    for (scanf("%d", &T); t <= T; t++) {
        printf("Case #%d: ", t);
        lint n;
        scanf("%lld", &n);
        string s = to_string(n);
        int len = s.size();
        for (int i = 0; i < len; i++) {
            int j = i;
            while (j + 1 < len && s[j + 1] == s[j]) j++;
            if (j + 1 == len) {
                printf("%lld\n", n);
                break;
            }
            if (s[j + 1] < s[i]) {
                s[i]--;
                for (j = i + 1; j < len; j++)
                    s[j] = '9';
                printf("%lld\n", stoll(s));
                break;
            }
        }        
    }        
    return 0;
}
