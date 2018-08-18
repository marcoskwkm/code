// WA

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

string s;

int go_left(int i, int cur) {
    int ans = 0;
    while (1) {
        ans = max(ans, cur);
        if (s[i] == '.' || s[i] == '#') {
            if (i - 1 < 0) return ans;
            else if (s[i - 1] != '#') {
                i--;
                continue;
            }
            else if (i - 2 < 0) return ans;
            else if (s[i - 2] == '*') {
                i -= 2;
                continue;
            }
            assert(cur > 0);
            if (cur > 1 && s[i - 2] == '.') {
                i -= 2;
                continue;
            }
            else {
                cur--, i--;
                continue;
            }
        }
        else if (s[i] == '*') {
            s[i] = '.';
            cur++;
            continue;
        }
        else abort();
    }
}                

int go_right(int i, int cur) {
    int ans = 0;
    while (1) {
        ans = max(ans, cur);
        if (s[i] == '.' || s[i] == '#') {
            if (i + 1 == (int)s.size()) return max(ans, go_left(i, cur));
            else if (s[i + 1] != '#') {
                i++;
                continue;
            }
            else if (i + 2 == (int)s.size()) return max(ans, go_left(i, cur));
            else if (s[i + 2] == '*') {
                i += 2;
                continue;
            }
            else if (cur == 0 || s[i] == '#') return max(ans, go_left(i, cur));
            else {
                s[i] = '*';
                cur--, i++;
                continue;
            }
        }
        else if (s[i] == '*') {
            s[i] = '.';
            cur++;
            continue;
        }
        else abort();
    }
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        cin >> s;
        int ans = 0, cur = 0;
        printf("Case #%d: %d\n", t, go_right(0, 0));
    }        
    return 0;
}
