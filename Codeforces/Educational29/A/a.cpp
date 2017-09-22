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
    cin >> n;
    while (n % 10 == 0) n /= 10;
    string s = to_string(n);
    string ss = s;
    reverse(s.begin(), s.end());
    printf("%s\n", s == ss ? "YES" : "NO");
    return 0;
}
