#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2.5e5 + 10;

int l[MAXN], r[MAXN];

int main() {
    int n;
    cin >> n;
    int ans = 0;
    stack<int> st;
    st.push(0);
    for (int i = 0; i < n; i++) {
        int h;
        scanf("%*d%d", &h);
        while (st.top() > h) st.pop();
        if (st.top() < h) {
            ans++;
            st.push(h);
        }
    }
    printf("%d\n", ans);
    return 0;
}
