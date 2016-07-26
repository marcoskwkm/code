#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

double r[MAXN], x[MAXN];

inline double get_x(int i, int j) {
    return x[i] + sqrt((r[i] + r[j])*(r[i] + r[j]) - (r[j] - r[i])*(r[j] - r[i]));
}

int main() {
    int n;
    while (scanf("%d", &n) > 0) {
        stack<int> st;
        double minx = LINF, maxx = -LINF;
        for (int i = 0; i < n; i++) {
            x[i] = 0;
            scanf("%lf", &r[i]);
            while (!st.empty()) {
                x[i] = max(x[i], get_x(st.top(), i));
                if (r[i] >= r[st.top()]) st.pop();
                else break;
            }
            st.push(i);
            minx = min(minx, x[i] - r[i]);
            maxx = max(maxx, x[i] + r[i]);
        }
        printf("%.8f\n", maxx - minx);
    }            
    return 0;
}
