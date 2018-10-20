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

bool check(int n, int k, int first) {
    if (k < v[first]) return 0;

    int at = v[first];
    for (int i = first - 1; i >= 0; i--) {
        at = (at == 1 ? k : at - 1);
        if (v[i] != -1 && v[i] != at) return 0;
    }

    at = v[first];
    for (int i = first + 1; i < n; i++) {
        at = (at == k ? 1 : at + 1);
        if (v[i] != -1 && v[i] != at) return 0;
    }
    return 1;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        int first = -1;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            if (v[i] != -1 && first == -1)
                first = i;
        }
        if (first == -1) {
            printf("inf\n");
            continue;
        }
        int at = v[first];
        bool ok = 1, found = 0;
        for (int i = first + 1; i < n; i++) {
            at++;
            if (v[i] == -1 || v[i] == at) continue;
            found = 1;
            if (v[i] > at) ok = 0;
            at -= v[i];
            break;
        }
        if (!found) {
            printf("inf\n");
            continue;
        }
        if (!ok) {
            printf("impossible\n");
            continue;
        }
        int ans = -1;
        for (int d = 1; d * d <= at; d++) {
            if (at % d) continue;
            if (check(n, d, first)) ans = max(ans, d);
            if (check(n, at / d, first)) ans = max(ans, at / d);
        }

        if (ans == -1) printf("impossible\n");
        else printf("%d\n", ans);
    }        
    return 0;
}
