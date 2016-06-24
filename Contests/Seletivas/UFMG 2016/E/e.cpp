#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int f[30];

int main() {
    string line;
    while (cin >> line) {
        for (char c: line)
            f[c - 'A']++;
    }
    vector< pair<int, char> > v;
    for (int i = 0; i < 26; i++)
        v.push_back(make_pair(-f[i], 'A' + i));

    sort(v.begin(), v.end());
    for (int i = 0; i < 26; i++)
        printf("%c %d\n", v[i].second, -v[i].first);
    
    return 0;
}
