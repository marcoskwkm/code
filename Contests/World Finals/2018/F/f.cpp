#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 2510;
const int MAXL = MAXN * 81;

pii last[2][MAXL];
int best[2][MAXL];

int main() {
    int n;
    cin >> n;
    vector<string> input;
    int sum = 0;
    int hi = 0;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;
        input.push_back(w);
        sum += w.size();
        hi = max<int>(hi, w.size());
    }
    sum += n - 1;

    int ans = 0, best_length = -1;
    for (int len = sum; len >= hi; len--) {
        int cur = 0, prv = 1;
        int at = 0;
        int line = 0;
        int got = 0;
        while (at < n) {
            int s = input[at++].size();
            while (at < n && s + 1 + (int)input[at].size() <= len) {
                int opt = 0;
                for (int i = -1; i <= 1; i++)
                    if (last[prv][s + i] == pii(line - 1, len))
                        opt = max(opt, best[prv][s + i]);
                last[cur][s] = pii(line, len);
                best[cur][s] = opt + 1;
                got = max(got, opt + 1);
                s += 1 + input[at++].size();
            }
            cur ^= 1;
            prv ^= 1;
            line++;
        }
        // printf("len = %d, got %d\n", len, got);
        if (got >= ans) {
            ans = got;
            best_length = len;
        }
    }

    printf("%d %d\n", best_length, ans);    
    return 0;
}
