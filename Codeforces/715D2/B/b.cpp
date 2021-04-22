#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        bool flag = 0;
        int qt = 0, qm = 0;
        for (int i = 0; i < 2; i++) {
            qt = qm = 0;
            for (char c: s) {
                if (c == 'T') {
                    qt++;
                } else {
                    qm++;
                    if (qm > qt) {
                        flag = 1;
                    }
                }
            }
            reverse(s.begin(), s.end());
        }
        printf("%s\n", (flag || (qt != 2 * qm)) ? "NO" : "YES");
    }
    return 0;
}
