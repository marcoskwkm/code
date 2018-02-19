#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    vector<pii> v;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        char c;
        scanf("%d %c", &x, &c);
        v.push_back(pii(x, c == '+' ? 0 : 1));
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 0; i < n - 1; i++)
        if (v[i].second == 1 && v[i + 1].second == 0)
            ans++;
    printf("%d\n", min(2, 1 + ans));
    return 0;
}
