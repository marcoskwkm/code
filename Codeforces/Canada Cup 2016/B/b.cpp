#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    lint n;
    char s;
    cin >> n >> s;
    n--;
    lint ans = 0;
    lint k = n / 4;
    ans += 16 * k;
    n -= k * 4;
    if (n == 1 || n == 3) ans += 7;
    if (s >= 'd') ans += 'f' - s;
    else ans += 3 + s - 'a';
    cout << ans + 1 << endl;    
    return 0;
}
