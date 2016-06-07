#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int mask[6];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 6; i++)
        mask[i] = (1 << 12) - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            string s;
            cin >> s;
            int m = 0;
            for (char c: s)
                m |= (1 << (c - 'A'));
            mask[j] &= m;
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 12; j++) {
            if (mask[i] & (1 << j))
                printf("%c", 'A' + j);
        }
        if (i < 5) printf(" ");
    }
    printf("\n");    
    return 0;
}
