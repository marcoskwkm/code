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
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int n;
        cin >> n;
        string lydia;
        cin >> lydia;
        printf("Case #%d: ", t);
        for (char c: lydia)
            printf("%c", 'E' + 'S' - c);
        printf("\n");
    }        
    return 0;
}
