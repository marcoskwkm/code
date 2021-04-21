#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, k;
        cin >> n >> k;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            v.push_back(x);
        }
        for (int i = 0; i < n; i++) {
            int take = min(k, v[i]);
            v[i] -= take;
            v.back() += take;
            k -= take;
        }
        for (int x: v) printf("%d ", x);
        printf("\n");
    }
    return 0;
}
