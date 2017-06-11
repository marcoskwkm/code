#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

map<int, int> seen[10];
lint fat[10];

int go(int n, vector<int> d, int len) {
    if (seen[len].find(n) != seen[len].end())
        return seen[len][n];
    int sum = 0;
    for (int x: d) sum += x;
    if (sum > len) return seen[len][n] = 1;
    int cur = 0;
    vector<int> nxtd(len);
    for (int i = 0; i < len - sum; i++)
        nxtd[cur++] = 0;
    int nxtsum = 0;
    for (int i = 1; i <= len; i++) {
        for (int j = 0; j < d[i - 1]; j++) {
            nxtd[cur++] = i;
            nxtsum += i;
        }
    }
    if (nxtsum > len) {
        lint ret = fat[len] / fat[len - sum];
        for (int i = 0; i < len; i++)
            ret /= fat[d[i]];
        return seen[len][n] = 1 + ret;
    }
        
    int ret = 1;
    do {
        int nxtn = 0;
        for (int x: nxtd) nxtn = 10*nxtn + x;
        if (nxtn == n) continue;
        ret += go(nxtn, nxtd, len);
    } while (next_permutation(nxtd.begin(), nxtd.end()));
    return seen[len][n] = ret;
}

int main() {
    fat[0] = 1;
    for (int i = 1; i < 10; i++)
        fat[i] = i * fat[i - 1];
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        printf("Case #%d: ", t);
        string s;
        cin >> s;
        int len = s.size();
        vector<int> d(len);
        vector<int> nxt(len);
        for (int i = 0; i < len; i++) {
            d[i] = s[i] - '0';
            nxt[d[i] - 1]++;
        }
        int n = stoi(s);
        printf("%d\n", go(n, d, len));
    }        
    return 0;
}
