#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        string s;
        cin >> s;
        stack<char> st;
        int ans = 0;
        for (char c: s) {
            if (!st.empty() && st.top() == c) {
                st.pop();
                ans += 10;
            }
            else st.push(c);
        }
        printf("Case #%d: %d\n", t, ans + 5 * (st.size() / 2));
    }        
    return 0;
}
