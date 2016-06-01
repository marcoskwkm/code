#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

int main() {
    lint ans = 1;
    string s;
    cin >> s;
    for (char c: s) {
        int d;
        if (isdigit(c)) d = c - '0';
        else if (isupper(c)) d = c - 'A' + 10;
        else if (islower(c)) d = c - 'a' + 36;
        else if (c == '-') d = 62;
        else d = 63;
        for (int i = 0; i < 6; i++)
            if ((d & (1 << i)) == 0)
                ans = (3 * ans) % MOD;
    }
    cout << ans << endl;        
    return 0;
}
