#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int rem[10];
string s;
int ans[200];
int len;

bool go(int i, bool free) {
    if (i == (int)s.size()) {
        int at = 0;
        while (ans[at] == 0) at++;
        for (int j = at; j < len; j++)
            printf("%d", ans[j]);
        printf("\n");
        return 1;
    }
    if (free) {
        for (int d = 9; d >= 0; d--) {
            if (rem[d] > 0) {
                rem[d]--;
                ans[len++] = d;
                if (go(i + 1, 1)) return 1;
                len--;
                rem[d]++;
            }
        }
        return 0;
    }        
    if (rem[s[i] - '0'] > 0) {
        rem[s[i] - '0']--;
        ans[len++] = s[i] - '0';
        if (go(i + 1, 0)) return 1;
        rem[s[i] - '0']++;
        len--;
    }
    for (int d = s[i] - '0' - 1; d >= 0; d--) {
        if (rem[d] > 0) {
            rem[d]--;
            ans[len++] = d;
            if (go(i + 1, 1)) return 1;
            len--;
            rem[d]++;
        }
    }
    return 0;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        cin >> s;
        int n = s.size();
        if (n > 20) {
            printf("99887766554433221100\n");
            continue;
        }
        fill(rem, rem + 10, 2);
        len = 0;
        go(0, 0);
    }
    return 0;
}
