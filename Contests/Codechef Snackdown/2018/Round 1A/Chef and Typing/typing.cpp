#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int type[300];

int main() {
    type['d'] = type['f'] = 0;
    type['j'] = type['k'] = 1;
    
    int t;
    for (cin >> t; t--;) {
        map<string, int> mp;
        int n;
        int ans = 0;
        for (cin >> n; n--;) {
            string word;
            cin >> word;
            auto it = mp.find(word);
            if (it != mp.end()) {
                ans += it->second / 2;
                continue;
            }
            int last = type[word[0]] ^ 1;
            int elapsed = 0;
            for (char c: word) {
                if (type[c] == last)
                    elapsed += 4;
                else
                    elapsed += 2;
                last = type[c];
            }
            ans += mp[word] = elapsed;
        }
        cout << ans << endl;
    }    
    return 0;
}
