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
    bool ok = 0;
    for (scanf("%d", &n); n--;) {
        int a, b;
        string s;
        cin >> s >> a >> b;
        if (a >= 2400 && a < b) ok = 1;
    }
    printf("%s\n", ok ? "YES":"NO");
    return 0;
}
