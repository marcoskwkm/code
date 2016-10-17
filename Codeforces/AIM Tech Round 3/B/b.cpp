#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int get_n(lint k) {
    lint l = 1, r = INF;
    while (l < r) {
        lint mid = (l + r) / 2;
        if (mid * (mid - 1) / 2 >= k)
            r = mid;
        else
            l = mid + 1;
    }
    if (l * (l - 1) / 2 != k) return -1;
    return l;
}

int main() {
    lint a00, a01, a10, a11;
    cin >> a00 >> a01 >> a10 >> a11;
    lint sum = a00 + a01 + a10 + a11;
    if (sum == 0) {
        printf("1\n");
        return 0;
    }
    int n = get_n(sum);
    int q0 = get_n(a00), q1 = get_n(a11);
    if (n == -1 || q0 == -1 || q1 == -1) {
        printf("Impossible\n");
        return 0;
    }
    if (a00 == a01 && a01 == a10 && a10 == 0)
        q0 = 0;
    if (a11 == a10 && a10 == a01 && a01 == 0)
        q1 = 0;

    if (q0 + q1 != n) {
        printf("Impossible\n");
        return 0;
    }

    bool ok = 1;
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        if (q1 && a10 >= q0) {
            a10 -= q0;
            ans[i] = 1;
            q1--;
        }
        else if (q0 > 0) q0--;
        else ok = 0;
    }
    
    if (!ok) {
        printf("Impossible\n");
        return 0;
    }
    for (int x: ans) printf("%d", x);
    printf("\n");
    
    return 0;
}
