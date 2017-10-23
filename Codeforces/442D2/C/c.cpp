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
    vector<int> sol;
    for (int i = 2; i <= n; i += 2)
        sol.push_back(i);
    for (int i = 1; i <= n; i += 2)
        sol.push_back(i);
    for (int i = 2; i <= n; i += 2)
        sol.push_back(i);
    printf("%d\n", (int)sol.size());
    for (int x: sol) printf("%d ", x);
    printf("\n");
    
    return 0;
}
