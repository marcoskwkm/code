#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10;

string s;
int n;
set<string> ans;
bool done[MAXN][3];

void go(int i, int k) {
    if (done[i][k]) return;
    done[i][k] = 1;
    if (i - 2 > 4 && k != 1) {
        ans.insert(s.substr(i - 2, 2));
        if (i - 4 > 4 && s.substr(i - 4, 2) == s.substr(i - 2, 2))
            go(i - 2, 1);
        else go(i - 2, 0);
    }
    if (i - 3 > 4 && k != 2) {
        ans.insert(s.substr(i - 3, 3));
        if (i - 6 > 4 && s.substr(i - 6, 3) == s.substr(i - 3, 3))
            go(i - 3, 2);
        else go(i - 3, 0);
    }
}

int main() {
    cin >> s;
    n = s.size();
    go(n, 0);
    printf("%d\n", (int)ans.size());
    for (const string &s: ans) printf("%s\n", s.c_str());
    return 0;
}
