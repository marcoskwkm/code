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
    vector<int> v(9);
    for (int i = 0; i < 9; i++)
        scanf("%d", &v[i]);
    printf("%d\n", min(v[0], min(v[1], v[2])) + min(v[3], min(v[4], v[5])) + min(v[6], min(v[7], v[8])));
    return 0;
}
