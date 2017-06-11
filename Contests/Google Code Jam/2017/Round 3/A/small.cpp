#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

unordered_set<int> seen;

void go(int n, vector<int> &d, int len) {
    seen.insert(n);
    int sum = 0;
    for (int x: d) sum += x;
    if (sum > len) return;
    int cur = 0;
    vector<int> nxtd(len);
    for (int i = 0; i < len - sum; i++)
        nxtd[cur++] = 0;
    for (int i = 1; i <= len; i++)
        for (int j = 0; j < d[i - 1]; j++)
            nxtd[cur++] = i;
    do {
        int nxtn = 0;
        for (int x: nxtd) nxtn = 10*nxtn + x;
        if (seen.find(nxtn) != seen.end()) continue;
        go(nxtn, nxtd, len);
    } while (next_permutation(nxtd.begin(), nxtd.end()));
}    

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        printf("Case #%d: ", t);
        string s;
        cin >> s;
        int len = s.size();
        vector<int> d(len);
        for (int i = 0; i < len; i++)
            d[i] = s[i] - '0';
        int n = stoi(s);
        seen.clear();
        go(n, d, len);
        printf("%d\n", (int)seen.size());
    }        
    return 0;
}
