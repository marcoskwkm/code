#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    string s;
    cin >> n >> s;
    int len = s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;
        if (w.size() == len) {
            int d = 0;
            for (int j = 0; j < len; j++)
                if (s[j] != w[j]) d++;
            if (d <= 1) ans++;
        }
        else if (w.size() == len - 1) {
            int d = 0, l = 0;
            for (int r = 0; r < len; r++) {
                if (w[l] == s[r]) l++;
                else d++;
            }
            if (d == 1) ans++;
        }
        else if (w.size() == len + 1) {
            int d = 0, l = 0;
            for (int r = 0; r < len + 1; r++) {
                if (w[r] == s[l]) l++;
                else d++;
            }
            if (d == 1) ans++;
        }
    }
    printf("%d\n", ans);    
    return 0;
}
