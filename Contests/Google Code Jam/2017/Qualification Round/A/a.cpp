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
        string s;
        int size;
        cin >> s >> size;
        int cnt = 0;
        for (int i = 0; i + size - 1 < (int) s.size(); i++) {
            if (s[i] == '-') {
                cnt++;
                for (int j = 0; j < size; j++)
                    s[i + j] = (s[i + j] == '+' ? '-' : '+');
            }
        }
        bool ok = 1;
        for (char c: s)
            if (c == '-')
                ok = 0;
        if (ok) printf("Case #%d: %d\n", t, cnt);
        else printf("Case #%d: IMPOSSIBLE\n", t);
    }        
    return 0;
}
