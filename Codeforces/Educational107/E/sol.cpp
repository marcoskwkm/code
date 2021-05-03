#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = 998244353;
const int MAXS = (int)3e5 + 10;

array<lint, MAXS> p2;
array<lint, MAXS> dp;

template <class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

lint go(const vector<string> &grid) {
    int w = 0;
    for_each(grid.begin(), grid.end(),
             [&](const string &row) { w += count(row.begin(), row.end(), 'o'); });

    lint ans = 0;
    for_each(grid.begin(), grid.end(), [&](const string &row) {
        int cnt = 0;
        for (size_t i = 0; i + 1 < row.size(); i++) {
            if (row[i] == '*' || row[i + 1] == '*') {
                cnt = 0;
                continue;
            }
            int q = w - 2 - cnt;
            ans = (ans + dp[cnt] * p2[q]) % MOD;
            cnt++;
        }
    });

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    p2[0] = 1;
    dp[0] = 1;
    for (int i = 1; i < n * m; i++) {
        p2[i] = (p2[i - 1] * 2) % MOD;
        dp[i] = (dp[i - 1] + 2 * (i >= 2 ? dp[i - 2] : 0)) % MOD;
    }

    vector<string> grid(n);
    readArray(grid, n);

    vector<string> rotated(m);
    for (int i = 0; i < m; i++) {
        rotated[i] = string(n, ' ');
        for (int j = 0; j < n; j++)
            rotated[i][j] = grid[j][i];
    }

    cout << (go(grid) + go(rotated)) % MOD << endl;
    return 0;
}
