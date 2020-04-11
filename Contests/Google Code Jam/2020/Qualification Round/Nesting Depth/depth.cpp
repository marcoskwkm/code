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
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s;
        cin >> s;
        int cnt = 0;
        printf("Case #%d: ", t);
        for (char c: s) {
            int q = c - '0';
            if (q > cnt) {
                for (int i = 0; i < q - cnt; i++)
                    printf("(");
            } else if (q < cnt) {
                for (int i = 0; i < cnt - q; i++)
                    printf(")");
            }
            cnt = q;
            printf("%c", c);
        }
        while (cnt--) printf(")");
        printf("\n");
    }
    return 0;
}
