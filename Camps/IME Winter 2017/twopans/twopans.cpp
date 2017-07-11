#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

bool done[MAXN];

int main() {
    int n;
    cin >> n;
    if (n == 1) printf("2\n1A 0X\n1B 0X\n");
    else {
        printf("%d\n", n);
        int cur = 0;
        for (int i = 0; i < n; i++) {
            int nxt = (cur + 1) % n;
            printf("%d%c %d%c\n", cur + 1, done[cur] ? 'B' : 'A', nxt + 1, done[nxt] ? 'B' : 'A');
            done[cur] = done[nxt] = 1;
            cur = (cur + 2) % n;
        }
    }
    return 0;
}
