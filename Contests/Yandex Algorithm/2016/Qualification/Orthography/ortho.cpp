#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    scanf("%d", &n);
    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v.push_back(s);
    }
    int len = v[0].size();
    for (int i = 0; i < n; i++) {
        bool ok = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int q = 0;
            for (int k = 0; k < len; k++)
                if (v[i][k] != v[j][k])
                    q++;
            if (q > 1) ok = 0;
        }
        if (ok) {
            printf("%s\n", v[i].c_str());
            return 0;
        }
    }
    return 0;
}
