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
    int t;
    for (scanf("%d", &t); t--;) {
        string s;
        cin >> s;
        set<string> all;
        for (size_t i = 0; i < s.size(); i++)
            for (size_t len = 1; i + len - 1 < s.size(); len++)
                all.insert(s.substr(i, len));
        reverse(s.begin(), s.end());
        bool ok = 1;
        for (size_t i = 0; i < s.size(); i++)
            for (size_t len = 1; i + len - 1 < s.size(); len++)
                if (all.find(s.substr(i, len)) == all.end())
                    ok = 0;
        printf("%s\n", ok ? "YES" : "NO");
    }
    return 0;
}
