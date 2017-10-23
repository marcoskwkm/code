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
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]);
    int ans = 0;
    stack<int> st;
    for (int x: v) {
        while (!st.empty() && st.top() > x) {
            st.pop();
            ans++;
        }
        if (st.empty() || st.top() < x) st.push(x);
    }
    cout << ans + st.size() << endl;
    return 0;
}
