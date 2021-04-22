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
        int n;
        cin >> n;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            v.push_back(x);
        }
        sort(v.begin(), v.end(), [](int a, int b) { return a % 2 < b % 2; });
        for (auto x: v) printf("%d ", x);
        printf("\n");
    }
    return 0;
}
