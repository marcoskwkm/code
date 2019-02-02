#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;
const int F_SIZE = 32;

string orig[MAXN];
vector<int> bucket[MAXN];

int main() {
    #ifndef HOME
    freopen("kaleidoscope.in", "r", stdin);
    freopen("kaleidoscope.out", "w", stdout);
    #endif
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> orig[i];
        int q = 0;
        for (char c: orig[i])
            if (isdigit(c))
                q += c - '0';
        bucket[q % 3].push_back(i);
    }

    for (int i = 0; i < k; i++) {
        if (bucket[i].size() > 0) continue;
        if (bucket[0].size() > 1) {
            bucket[i].push_back(bucket[0].back());
            bucket[0].pop_back();
        }
        else if (bucket[1].size() > 1) {
            bucket[i].push_back(bucket[1].back());
            bucket[1].pop_back();
        }
        else {
            bucket[i].push_back(bucket[2].back());
            bucket[2].pop_back();
        }
    }

    for (int i = 0; i < k; i++) {
        printf("%s", orig[bucket[i][0]].c_str());
        for (int j = 1; j < (int)bucket[i].size(); j++)
            printf(" %s", orig[bucket[i][j]].c_str());
        printf("\n");
    }    
    return 0;
}
