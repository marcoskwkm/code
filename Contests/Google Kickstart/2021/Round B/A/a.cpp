#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

void solve() {
    scanf("%*d");
    string s;
    cin >> s;
    vector<int> ans;
    for (size_t i = 0; i < s.size(); i++) {
        if (i == 0) {
            ans.push_back(1);
        } else {
            if (s[i] > s[i - 1]) {
                ans.push_back(ans[i - 1] + 1);
            } else {
                ans.push_back(1);
            }
        }
    }
    for (auto x: ans) printf(" %d", x);
    printf("\n");
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        solve();
    }
    return 0;
}
