#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int v[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < n; j++) {
            if (v[j] > v[j + 1]) {
                printf("%d %d\n", j + 1, j + 2);
                swap(v[j], v[j + 1]);
            }
        }
    }    
    return 0;
}
