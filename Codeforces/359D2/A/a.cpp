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
    lint x;
    cin >> n >> x;
    int ans = 0;
    while (n--) {
        char op;
        int q;
        scanf(" %c%d", &op, &q);
        if (op == '+') x += q;
        else if (x < q) ans++;
        else x -= q;
    }
    cout << x << " " << ans << endl;        
    return 0;
}
