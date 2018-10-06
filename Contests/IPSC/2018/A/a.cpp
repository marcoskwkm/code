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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            v.push_back(x);
        }
        vector<int> sol;
        for (int x: v) {
            if (x >= 100) sol.push_back(100);
            else if (x >= 10) sol.push_back(10);
            else sol.push_back(1);
        }
        sol.back() = 1;
        for (int x: sol) printf("%d ", x);
        printf("\n");
    }        
    return 0;
}
