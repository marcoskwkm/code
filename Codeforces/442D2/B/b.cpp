#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    string s;
    cin >> s;
    vector<int> acc;
    acc.push_back(0);
    for (char c: s)
        acc.push_back(acc.back() + (c == 'b'));
    int ans = 0;
    for (size_t i = 0; i < s.size(); i++) {
        for (size_t j = i; j <= s.size(); j++) {
            int got = s.size();
            got -= acc[i];
            int lm = j - i;
            got -= lm - (acc[j] - acc[i]);
            got -= acc[s.size()] - acc[j];
            ans = max(ans, got);
        }
    }
    cout << ans << endl;            
    return 0;
}
