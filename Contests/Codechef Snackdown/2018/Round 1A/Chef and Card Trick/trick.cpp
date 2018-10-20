#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int v[MAXN];

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        int low = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            if (v[i] <= v[low]) low = i;
        }
        while (low > 0 && v[low - 1] == v[low]) low--;

        rotate(v, v + low, v + n);

        bool ok = 1;
        for (int i = 0; i + 1 < n; i++)
            if (v[i] > v[i + 1]) ok = 0;

        printf("%s\n", ok ? "YES" : "NO");
    }        
    return 0;
}
