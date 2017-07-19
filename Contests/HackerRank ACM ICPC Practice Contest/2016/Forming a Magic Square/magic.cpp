#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    vector<vector<int>> magic_squares;
    vector<int> s;
    for (int i = 1; i <= 9; i++)
        s.push_back(i);
    do {
        int sum = s[0] + s[1] + s[2];
        bool ok = 1;
        for (int i = 0; i < 3; i++) {
            if (s[3*i] + s[3*i + 1] + s[3*i + 2] != sum) ok = 0;
            if (s[i] + s[i + 3] + s[i + 6] != sum) ok = 0;
        }
        if (s[0] + s[4] + s[8] != sum) ok = 0;
        if (s[2] + s[4] + s[6] != sum) ok = 0;
        if (ok) magic_squares.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    int ans = INF;
    vector<int> square;
    for (int i = 0; i < 9; i++) {
        int x;
        scanf("%d", &x);
        square.push_back(x);
    }
    for (const auto &v: magic_squares) {
        int got = 0;
        for (int i = 0; i < 9; i++)
            got += abs(v[i] - square[i]);
        ans = min(ans, got);
    }
    cout << ans << endl;             
    return 0;
}
