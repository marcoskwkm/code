#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int q[20];

int numdigits(int n) {
    if (n == 0) return 1;
    int ret = 0;
    while (n) {
        ret++;
        n /= 10;
    }
    return ret;
}

int main() {
    string num, s;
    cin >> num >> s;
    int total = 0;
    for (char c: num) {
        q[c - '0']++;
        total++;
    }
    int nd = 1;
    while (1) {
        int qd = total - nd;
        if (numdigits(qd) == nd) break;
        nd++;
    }
    nd = total - nd;
    int tmp = nd;
    while (tmp) {
        int d = tmp%10;
        q[d]--;
        tmp /= 10;
    }

    int s_before = -1;
    for (char c: s) {
        if (c != s[0] && s_before == -1) {
            if (c < s[0]) s_before = 1;
            else s_before = 0;
        }
        q[c - '0']--;
    }
    if (s_before == -1) s_before = 0;
    int lim = s[0] - '0';
    if (s_before == 1) lim--;
    
    int first = -1;
    if (s[0] == '0') {
        for (int d = 1; d < 10; d++) {
            if (q[d]) {
                first = d;
                break;
            }
        }
    }
    else {
        for (int i = 1; i <= lim; i++) {
            if (q[i]) {
                first = i;
                break;
            }
        }
    }
    if (first != -1) {
        printf("%d", first);
        q[first]--;
    }
    else printf("%s", s.c_str());
    
    for (int d = 0; d <= lim; d++) {
        for (int i = 0; i < q[d]; i++)
            printf("%d", d);
    }
    if (first != -1) printf("%s", s.c_str());
    for (int d = lim+1; d < 10; d++) {
        for (int i = 0; i < q[d]; i++)
            printf("%d", d);
    }    
    printf("\n");
    return 0;
}
