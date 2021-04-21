#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    cin >> n;
    lint m = 1;
    vector<int> ans;
    for (int i = 1; i < n; i++) {
        if (__gcd(n, i) == 1) {
            ans.push_back(i);
            m = (m * i) % n;
        }
    }
    if (m != 1) {
        ans.pop_back();
    }
    printf("%d\n", (int)ans.size());
    for (auto x: ans) printf("%d ", x);
    printf("\n");
    return 0;
}
