#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int A = 1234567, B = 123456, C = 1234;
    int n;
    scanf("%d", &n);
    for (int a = 0; a*A <= n; a++)
        for (int b = 0; a*A + b*B <= n; b++)
            if ((n - a*A - b*B) % C == 0) {
                printf("YES\n");
                return 0;
            }
    printf("NO\n");
    return 0;
}
