#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)4e6 + 10;

int seq[MAXN];

int main() {
    string line;
    for (int i = 0; i < 2; i++) {
        if (i == 1) continue;
        cin >> line;
        stack<int> s;
        int len = 0;
        for (char c: line) {
            int x = 0;
            c -= 33;
            for (int j = 0; j < 4; j++) {
                int d = c % 3;
                c /= 3;
                if (d == 2) {
                    x = -1;
                    break;
                }
                x = (x << 1) + d;
            }
            if (x == -1) printf("?\n");
            else printf("%d\n", x);
        }            
    }            
    return 0;
}
