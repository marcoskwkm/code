#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

string v[MAXN][2];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        cin >> v[i][0] >> v[i][1];
    while (m--) {
        string a, b;
        cin >> a >> b;
        bool ok = 0;
        for (int i = 0; i < n; i++)
            if (a == v[i][0] && b == v[i][1])
                ok = 1;
        printf("%s\n", ok ? "Nao e a mamae" : "nao e o Nao e a mamae");        
    }    
    return 0;
}
