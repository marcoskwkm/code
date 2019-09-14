#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int v[MAXN];
lint n, c, t;

bool go(lint q) {
    int cnt = 0;
    lint cur = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] + cur > q) {
            cnt++;
            cur = v[i];
        } else {
            cur += v[i];
        }
    }
    return cnt + 1 <= c;
}
    
int main() {
    cin >> n >> c >> t;

    lint sum = 0;
    lint l = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        sum += v[i];
        l = max<lint>(l, v[i]);
    }

    lint r = sum;
    while (l < r) {
        int mid = (l + r) / 2;
        if (go(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << (l + t - 1) / t << endl;    
    return 0;
}
