#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        string s1, s2;
        cin >> s1 >> s2;
        int ans = 0;
        for (char c: s1)
            if (s2[ans] == c)
                if (++ans == (int)s2.size())
                    break;
        printf("%s\n", ans == (int)s2.size() ? "YES" : "NO");
    }    
    return 0;
}
