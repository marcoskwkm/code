#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2010;

char str[MAXN];
char obj[MAXN];
int n;
vector<int> sol;

void fail() {
    printf("-1\n");
    exit(0);
}

void make(int x) {
    if (x == 0) return;
    sol.push_back(x);
    reverse(str + n - x, str + n);
    rotate(str, str + n - x, str + n);
}

int main() {
    cin >> n;
    scanf("%s", str);
    scanf("%s", obj);
    int l, r;
    if (n & 1) l = n / 2;
    else l = (n - 1) / 2;
    r = (l + 1) % n;

    // debug("l = %d, r = %d\n", l, r);
    int cur = 1;

    for (int i = n - 1; i >= 0; i--) {
        // debug("i = %d, str = %s\n", i, str);
        bool found = 0;
        for (int j = 0; j <= i; j++) {
            if (str[j] == (cur ? obj[l] : obj[r])) {
                // debug("found %c at j = %d\n", str[j], j);
                found = 1;
                make(n); make(j + 1); make(i - j);
                break;
            }
        }
        if (!found) fail();
        if (cur) l = (l ? l : n) - 1;
        else r = (r + 1) % n;
        cur ^= 1;
    }
    if (n % 2 == 0) make(n);
    // debug("%s\n", str);
    printf("%d\n", (int)sol.size());
    for (int x: sol) printf("%d ", x);
    printf("\n");
    return 0;
}
