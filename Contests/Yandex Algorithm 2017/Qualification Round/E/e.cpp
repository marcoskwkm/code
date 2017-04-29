#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

struct KMP {
    string pattern;
    int len;
    // f[i] = the size of longest preffix that is a suffix of p[0..i-1]    
    vector<int> f;
    
    KMP(string p) {
        pattern = p;
        len = p.size();
        f.resize(len + 2);
        f[0] = f[1] = 0;
        for (int i = 2; i <= len; i++) {
            int now = f[i - 1];
            while (1) {
                if (p[now] == p[i - 1]) {
                    f[i] = now + 1;
                    break;
                }
                if (now == 0) {
                    f[i] = 0;
                    break;
                }
                now = f[now];
            }
        }
    }
};

bool has[MAXN];

int main() {
    string s;
    cin >> s;
    KMP kmp(s);
    lint ans = 0;
    for (int i = 1; (int)i <= s.size(); i++) {
        int p = i;
        while (p > 0) {
            if (has[kmp.f[p]]) {
                ans += kmp.f[p];
                break;
            }
            p = kmp.f[p];
        }
        has[kmp.f[i]] = 1;
    }
    printf("%lld\n", ans);
    return 0;
}
