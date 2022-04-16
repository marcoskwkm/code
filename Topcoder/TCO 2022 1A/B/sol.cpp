#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXS = 110;

long double binom[MAXS][MAXS];

long double get_binom(int n, int k) {
    k = min(k, n - k);
    if (k < 0) {
        return 0;
    } else if (k == 0) {
        return 1;
    } else if (binom[n][k] == binom[n][k]) {
        return binom[n][k];
    }

    return binom[n][k] = get_binom(n - 1, k - 1) + get_binom(n - 1, k);
}

long double calc_p(int n, int d, int s) {
    long double cnt = 0;

    for (int k = 0; k <= n; k++) {
        cnt += get_binom(n, k) * get_binom(s - k * d - 1, n - 1) * (k % 2 == 1 ? -1 : 1);
    }

    for (int i = 0; i < n; i++) {
        cnt /= d;
    }

    return cnt;
}

struct SingleOrDouble {
    double probAlice(int n, int d, int a, int b) {
        memset(binom, -1, sizeof(binom));
        long double pa = calc_p(n, d, a);
        long double pb = calc_p(n, d, b);

        return pa * (1 + pb) / (1 - (1 - pa - pb) * (pb + 1));
    }
};

#ifdef HOME
int main() {
    int n, d, a, b;
    cin >> n >> d >> a >> b;
    cout << setprecision(16) << SingleOrDouble().probAlice(n, d, a, b) << endl;
    return 0;
}
#endif
