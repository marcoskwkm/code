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
    string s;
    cin >> s;
    int cur = 1;
    int l = 0, r = 2;
    vector<int> ans({1});
    for (char c: s) {
        if (c == '<') ans.push_back(r++);
        else ans.push_back(l--);
    }
    for (int x: ans) printf("%d ", x - l);
    return 0;
}
